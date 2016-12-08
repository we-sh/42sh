#include "shell.h"
#include <dirent.h>

#define NL_SIZE	(sizeof("\n") - 1)
#define NL				"\n"

static void		s_concat_buffer(size_t ref_size,
								size_t filename_size,
								char *filename,
								t_buffer *buffer)
{
	ft_memcpy(buffer->bytes + buffer->size,
			filename,
			filename_size);
	buffer->size += filename_size;
	ft_memset(buffer->bytes + buffer->size, ' ',
			ref_size - filename_size);
	buffer->size += ref_size - filename_size;
}

static int		s_fill_buffer(t_list *head,
							const int ref_size,
							t_buffer *buffer)
{
	t_node_dir	*node_dir;
	t_list		*pos;
	int			y_diff;
	size_t		filename_count;
	size_t		filename_by_line;

	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
	y_diff = 0;
	filename_count = 0;
	pos = head;
	while ((pos = pos->next) && (pos != head))
	{
		if (filename_count % filename_by_line == 0)
		{
			ft_memcpy(buffer->bytes + buffer->size, NL, NL_SIZE);
			buffer->size += NL_SIZE;
			y_diff += 1;
		}
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		s_concat_buffer(ref_size,
						node_dir->filename_size, node_dir->filename,
						buffer);
		filename_count += 1;
	}
	return (y_diff);
}

static int		s_display_completion(t_list *head,
										const int fd,
										const int list_dir_size,
										const int ref_size)
{
	size_t		buffer_size_max;
	t_buffer	buffer;
	int			y_diff;

	buffer_size_max = NL_SIZE + (ref_size + NL_SIZE) * list_dir_size;
	buffer.size = 0;
	buffer.bytes = (char *)malloc(buffer_size_max);
	ASSERT(buffer.bytes != NULL);
	y_diff = s_fill_buffer(head, ref_size, &buffer);
	if (!y_diff)
	{
		log_error("s_fill_buffer() failed");
		free(buffer.bytes);
		return (0);
	}
	termcaps_write(fd, buffer.bytes, buffer.size);
	free(buffer.bytes);
	while (y_diff--)
		caps__print_cap(CAPS__UP, 0);
	caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	return (1);
}

int				key__completion(t_termcaps_context *context)
{
	t_buffer	match;
	t_list		head;
	size_t		ref_size;
	size_t		list_dir_size;
	t_node_dir	*node_dir;

	ref_size = key__completion_list_dir(context, &head, &match) + 1;
	ASSERT(ref_size);
	list_dir_size = list_size(&head);
	if (list_dir_size == 1)
	{
		node_dir = CONTAINER_OF(head.next, t_node_dir, list);
		command_add_string(node_dir->filename_size - match.size,
										node_dir->filename + match.size,
										&context->command);
		if (node_dir->d_type == DT_DIR)
			command_add_string(sizeof("/") - 1, "/", &context->command);
	}
	else
	{
		s_display_completion(&head, context->fd, list_dir_size, ref_size);
	}
	list_dir__destroy(&head);
	return (1);
}

static int		s_get_matchs(char *path, char *lookfor, t_list *matchs, size_t *ref_size)
{
	DIR				*dp;
	struct dirent	*ep;
	t_node_dir		*new;

	ASSERT(dp = opendir(path));
	while ((ep = readdir(dp)))
	{
		if ((lookfor == NULL && ep->d_name[0] == '.') ||
			ft_strcmp(lookfor, ep->d_name))
			continue ;
		new = node_dir__create(ep);
		if (new == NULL)
			return (0);
		list_push_back(&new->list, matchs);
		if (new->filename_size > *ref_size)
			*ref_size = new->filename_size;
	}
	closedir(dp);
	return (0);
}

static int		s_match_binaries(char *lookfor, t_list *matchs)
{
	char	*env_path;
	char	**paths;
	size_t	i;

	env_path = env_get_path(NULL);
	ASSERT(env_path != NULL);
	paths = ft_strsplit(env_path, ':');
	ASSERT(paths != NULL);
	i = 0;
	while (paths[i])
	{
		if (!s_get_matchs(paths[i], lookfor, matchs))
			return (0);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (1);
}

static int		s_identify_lookfor(char *word, size_t word_size,
									char **path, char **lookfor)
{
	size_t		i;

	i = word_size - 1;
	while (i >= 0)
	{
		if (word[i] == '/')
			break ;
		i--;
	}
	if (i < 0)
	{
		i = 0;
		*path = NULL;
		*lookfor = word;
	}
	else
	{
		// not safe ?
		i += 1;
		ft_memmove(word + i + 1, word + i, word_size - i);
		word[i] = '\0';
		word[word_size + 1] = '\0';
		*path = word;
		if (i == word_size - 1)
			*lookfor = NULL;
		else
			*lookfor = word + i + 1;
	}
	return (1);
}

static void		s_match_last_word(char *cmd, size_t cmd_size, size_t *word_size)
{
	size_t		start;
	size_t		len;
	size_t		i;

	i = cmd_size - 1;
	while (i >= 0)
	{
		if (ft_isspace(cmd[i]))
			break ;
		i--;
	}
	if (i < 0)
		i = 0;
	start = i;
	len = cmd_size - i;
	ft_memmove(cmd, cmd + start, len);
	*word_size = len;
}

extern int		key__completion(t_termcaps_context *context)
{
	size_t		buf_size;
	char		buf[1024];
	char		*path;
	char		*lookfor;
	t_list		matchs;

	ASSERT(command_to_buffer(&context->command,
				sizeof(buf) - 1, &buf_size, buf));
	s_match_last_word(buf, buf_size, &buf_size);
	s_split_word(buf, buf_size, &path, &lookfor);
	INIT_LIST_HEAD(&matchs);
	if (path == NULL)
		s_match_binaries(lookfor, &matchs);
	else
		s_get_matchs(path.bytes, lookfor, &matchs);
	if (list_size(matchs) == 1)
		s_update_command(lookfor, 
}

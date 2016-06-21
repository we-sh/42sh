#include "shell.h"
#include <dirent.h>

#define ENDL_SIZE	(sizeof("\n") - 1)
#define ENDL				"\n"

size_t	s_list_dir(const char *path,
				   const size_t match_size,
				   const char *match,
				   t_list *head)
{
	DIR				*dp;
	struct dirent	*ep;
	t_node_dir		*new;
	size_t			ref_size;

	INIT_LIST_HEAD(head);
	ASSERT((dp = opendir(path)) != NULL);
	ref_size = 0;
	while ((ep = readdir(dp)) != NULL)
	{
		if ((!match_size && ep->d_name[0] == '.') ||
			ft_memcmp(ep->d_name, match, match_size))
			continue ;
		new = node_dir__create(ep->d_name);
		if (!new)
		{
			list_dir__destroy(head);
			return (0);
		}
		list_push_back(&new->list, head);
		if (new->filename.size > ref_size)
			ref_size = new->filename.size;
	}
	ASSERT(!closedir(dp));
	return (ref_size);
}

static int	s_get_path_and_match(t_termcaps_context *context, char **out_path, t_buffer *out_match)
{
	char		*match;
	size_t		cmd_size;
	char		cmd[1024];

	ASSERT(list_head__command_line_to_buffer(&context->command_line,
											 sizeof(cmd) - 1,
											 &cmd_size,
											 cmd));
	cmd[cmd_size] = 0;
	if (cmd_size == 0 || cmd[cmd_size - 1] == ' ')
	{
		*out_path = "./";
		out_match->bytes = NULL;
		out_match->size = 0;
		return (1);
	}
	while (--cmd_size > 0)
	{
		if (ft_isspace(cmd[cmd_size]))
		{
			cmd_size++;
			break ;
		}
	}
	match = ft_strrchr(cmd + cmd_size, '/');
	if (match == NULL)
	{
		*out_path = "./";
		match = cmd + cmd_size;
	}
	else
	{
		*out_path = cmd + cmd_size;
		ft_memmove(match + 2, match + 1, ft_strlen(match + 1) + 1);
		match[1] = 0;
		match += 2;
	}
	out_match->bytes = match;
	out_match->size = ft_strlen(match);
	return (1);
}

static int		s_fill_buffer(t_list *head,
							  const int ref_size,
							  const size_t buffer_size_max,
							  char *buffer)
{
	size_t		buffer_offset;
	size_t		filename_by_line;
	size_t		filename_count;
	t_node_dir	*node_dir;
	t_list		*pos;
	int			y_diff = 0;

	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
	filename_count = 0;
	buffer_offset = 0;
	LIST_FOREACH(head, pos)
	{
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		ASSERT(buffer_offset + ref_size < buffer_size_max);
		if (filename_count++ % filename_by_line == 0)
		{
			ft_memcpy(buffer + buffer_offset, ENDL, ENDL_SIZE);
			buffer_offset += ENDL_SIZE;
			y_diff++;
		}
		ft_memcpy(buffer + buffer_offset, node_dir->filename.bytes, node_dir->filename.size);
		buffer_offset += node_dir->filename.size;
		ft_memset(buffer + buffer_offset, ' ', ref_size - node_dir->filename.size);
		buffer_offset += ref_size - node_dir->filename.size;
	}
	buffer[buffer_offset] = 0;
	return (y_diff);
}

static int		s_display_completion(t_list *head,
									 const int fd,
									 const int list_dir_size,
									 const int ref_size)
{
	size_t		buffer_size_max;
	char		*buffer;
	int			y_diff;

	buffer_size_max = (ref_size + ENDL_SIZE) * list_dir_size;
	buffer = (char *)malloc(buffer_size_max);
	ASSERT(buffer != NULL);
	y_diff = s_fill_buffer(head, ref_size, buffer_size_max, buffer);
	if (!y_diff)
	{
		log_error("s_fill_buffer() failed");
		free(buffer);
		return (0);
	}
	termcaps_write(fd, buffer, ft_strlen(buffer));
	free(buffer);
	while (y_diff--)
		caps__print_cap(CAPS__UP, 0);
	caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	return (1);
}

int		key__completion(t_termcaps_context *context)
{
	char		*path;
	t_buffer	match;
	t_list		head;
	size_t		ref_size;
	size_t		list_dir_size;

	ASSERT(s_get_path_and_match(context, &path, &match));
	ref_size = s_list_dir(path, match.size, match.bytes, &head) + 1;
	ASSERT(ref_size != 1);
	list_dir_size = list_size(&head);
	if (list_dir_size == 1)
	{
		t_node_dir *node_dir = CONTAINER_OF(head.next, t_node_dir, list);
		termcaps_string_to_command_line(node_dir->filename.size - match.size,
										node_dir->filename.bytes + match.size,
										&context->command_line);
	}
	else
	{
		s_display_completion(&head, context->fd, list_dir_size, ref_size);
	}
	list_dir__destroy(&head);
	return (1);
}

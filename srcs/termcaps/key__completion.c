#include "shell.h"
#include <dirent.h>

typedef struct	s_node_dir
{
	t_buffer		filename;
	t_list			list;
}				t_node_dir;

static t_node_dir	*node_dir__create(const char *filename)
{
	void		*addr;
	t_node_dir	*new;
	size_t		filename_size;

	filename_size = ft_strlen(filename);
	addr = malloc(sizeof(t_node_dir) + filename_size + 1);
	if (!addr)
		return (NULL);
	new = addr;
	new->filename.bytes = addr + sizeof(t_node_dir);
	new->filename.size = filename_size;
	ft_memcpy(new->filename.bytes, filename, filename_size + 1);
	return (new);
}

static void		list_dir__destroy(t_list *head)
{
	t_list		*pos;
	t_list		*safe;
	t_node_dir	*node_dir;

	safe = head->next;
	while ((pos = head) && (pos != head) && (safe = safe->next))
	{
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		free(node_dir->filename.bytes);
	}
}

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
	if ((dp = opendir(path)) == NULL)
		return (0);
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
	if (closedir(dp) != 0)
		log_error("closedir() failed");
	return (ref_size);
}

void	s_get_path_and_match(size_t cmd_size,
		char *cmd,
		char **out_path,
		t_buffer *out_match)
{
	char		*match;

	if (cmd_size == 0 || cmd[cmd_size - 1] == ' ')
	{
		*out_path = "./";
		out_match->bytes = NULL;
		out_match->size = 0;
		return ;
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
}

#define ENDL_SIZE	(sizeof("\n") - 1)
#define ENDL				"\n"

int		key__completion(t_termcaps_context *context)
{
	size_t		cmd_size;
	char		cmd[1024];
	char		*path;
	t_buffer	match;
	t_list		head;

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(cmd) - 1,
				&cmd_size,
				cmd))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (-1);
	}
	cmd[cmd_size] = 0;

	s_get_path_and_match(cmd_size, cmd, &path, &match);

	size_t	ref_size = s_list_dir(path, match.size, match.bytes, &head);
	if (!ref_size)
	{
		log_error("s_list_dir() failed");
		return (0);
	}
	ref_size += 1;
	log_debug("ref_size %d", ref_size);

	size_t list_dir_size = list_size(&head);
	if (list_dir_size == 1)
	{
		t_list *node = list_nth(&head, 1);
		t_node_dir *node_dir = CONTAINER_OF(node, t_node_dir, list);

		if (!termcaps_string_to_command_line(node_dir->filename.size - match.size,
											 node_dir->filename.bytes + match.size,
											 &context->command_line))
		{
			log_error("termcaps_string_to_command_line() failed");
		}
	}
	else
	{
		size_t	buffer_size_max = (ref_size + ENDL_SIZE) * list_dir_size;
		char	*buffer = malloc(buffer_size_max);
		if (!buffer)
		{
			log_fatal("malloc() failed size %d", buffer_size_max);
			return (0);
		}
		size_t	buffer_offset = 0;

		size_t	filename_by_line = caps__win(WIN_COLUMNS) / ref_size;
		size_t	filename_count = 0;

		int	   y_diff = 0;

		t_list *pos;
		LIST_FOREACH(&head, pos)
		{
			t_node_dir *node_dir = CONTAINER_OF(pos, t_node_dir, list);

			if (buffer_offset + ref_size >= buffer_size_max)
			{
				log_fatal("buffer overflow buffer_size_max %zu", buffer_size_max);
				break ;
			}
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
		write(context->fd, buffer, buffer_offset);
		free(buffer);
		while (y_diff)
		{
			caps__print_cap(CAPS__UP, 0);
			y_diff--;
		}
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
	}

	list_dir__destroy(&head);

	return (1);
}

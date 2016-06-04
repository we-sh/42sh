#include "shell.h"
#include <dirent.h>

typedef struct	s_node_dir
{
	t_buffer		filename;
	t_list			list;
}				t_node_dir;

static t_node_dir	*node_dir__create(const char *filename)
{
	t_node_dir	*new;

	new = malloc(sizeof(t_node_dir));
	if (!new)
		return (NULL);
	new->filename.size = ft_strlen(filename);
	new->filename.bytes = ft_strdup(filename);
	if (!new->filename.bytes)
	{
		free(new);
		return (NULL);
	}
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
		free(node_dir);
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
	ref_size = 0;
	dp = opendir(path);
	if (dp != NULL)
	{
		while ((ep = readdir(dp)) != NULL)
		{
			if ((match_size > 0 && match[0] == '.') ||
				!ft_memcmp(ep->d_name, ".", sizeof(".") - 1))
				continue ;
			if (!ft_memcmp(ep->d_name, match, match_size))
			{
				new = node_dir__create(ep->d_name);
				if (!new)
				{
					log_error("node_dir__create() failed");
					list_dir__destroy(head);
					if (closedir(dp) != 0)
						log_error("closedir() failed");
					return (0);
				}
				if (new->filename.size > ref_size)
					ref_size = new->filename.size;
				list_push_back(&new->list, head);
			}
		}
		if (closedir(dp) != 0)
			log_error("closedir() failed");
	}
	return (ref_size);
}

void	s_get_path_and_match(size_t cmd_size,
		char *cmd,
		char **out_path,
		t_buffer *out_match)
{
	char		*path;
	char		*match;

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
		path = "./";
		match = cmd + cmd_size;
	}
	else
	{
		path = cmd + cmd_size;
		match++;
		ft_memmove(match + 1, match, ft_strlen(match) + 1);
		*match = 0;
		match++;
	}
	*out_path = path;
	out_match->bytes = match;
	out_match->size = ft_strlen(match);
}

int		key__completion(t_internal_context *context)
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

	if (cmd_size == 0 || cmd[cmd_size - 1] == ' ')
	{
		path = "./";
		match.bytes = NULL;
		match.size = 0;
	}
	else
	{
		s_get_path_and_match(cmd_size, cmd, &path, &match);
	}

	size_t	ref_size = s_list_dir(path, match.size, match.bytes, &head);
	if (!ref_size)
	{
		log_error("s_list_dir() failed");
		return (0);
	}
	ref_size += 1;
	log_debug("ref_size %d", ref_size);

	if (list_size(&head) == 1)
	{
		t_list *node = list_nth(&head, 1);
		if (node == &head)
			log_fatal("node == head");

		t_node_dir *node_dir = CONTAINER_OF(node, t_node_dir, list);
		log_debug("node_dir->filename %.*s", node_dir->filename.size, node_dir->filename.bytes);

		if (!termcaps_string_to_command_line(node_dir->filename.size - match.size,
											 node_dir->filename.bytes + match.size,
											 &context->command_line))
		{
			log_error("termcaps_string_to_command_line() failed");
		}
	}
	else
	{
		size_t	buffer_size_max = (ref_size + sizeof("\n\r") - 1) * caps__win(WIN_LINE);
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
				ft_memcpy(buffer + buffer_offset, "\n\r", sizeof("\n\r") - 1);
				buffer_offset += sizeof("\n\r") - 1;
				y_diff++;
			}
			ft_memcpy(buffer + buffer_offset, node_dir->filename.bytes, node_dir->filename.size);
			buffer_offset += node_dir->filename.size;
			ft_memset(buffer + buffer_offset, ' ', ref_size - node_dir->filename.size);
			buffer_offset += ref_size - node_dir->filename.size;
		}
		write(1, buffer, buffer_offset);
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

#include "shell.h"
#include <dirent.h>

typedef struct	s_node_dir
{
	char			*filename;
	t_list			list;
}				t_node_dir;

static t_list	*node_dir__create(const char *filename)
{
	t_node_dir	*new;

	new = malloc(sizeof(t_node_dir));
	if (!new)
		return (NULL);
	new->filename = ft_strdup(filename);
	if (!new->filename)
	{
		free(new);
		return (NULL);
	}
	return (&new->list);
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
		free(node_dir->filename);
		free(node_dir);
	}
}

bool	s_list_dir(const char *path,
		const size_t match_size,
		const char *match,
		t_list *head)
{
	DIR				*dp;
	struct dirent	*ep;
	t_list			*new;

	//log_debug("path %s match %s match_size %zu", path ? path : "Null", match ? match : "Null", match_size);
	INIT_LIST_HEAD(head);
	dp = opendir(path);
	if (dp != NULL)
	{
		while ((ep = readdir(dp)) != NULL)
		{
			if (!ft_memcmp(ep->d_name, ".", sizeof(".")) ||
				!ft_memcmp(ep->d_name, "..", sizeof("..")))
				continue ;
			log_debug("ep->d_name {%s}", ep->d_name);
			if (!ft_memcmp(ep->d_name, match, match_size))
			{
				new = node_dir__create(ep->d_name);
				if (!new)
				{
					log_error("node_dir__create() failed");
					list_dir__destroy(head);
					if (closedir(dp) != 0)
						log_error("closedir() failed");
					return (false);
				}
				list_push_back(new, head);
			}
		}
		if (closedir(dp) != 0)
			log_error("closedir() failed");
	}
	return (true);
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
	int			y_diff;

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

	if (!s_list_dir(path, match.size, match.bytes, &head))
	{
		log_error("s_list_dir() failed");
		return (0);
	}

	if (list_size(&head) == 1)
	{
		t_list *node = list_nth(&head, 1);
		log_debug("log == &head ? %s", node == &head ? "true":"false");

		t_node_dir *node_dir = CONTAINER_OF(node, t_node_dir, list);
		log_debug("node_dir->filename %s", node_dir->filename);

		if (!termcaps_string_to_command_line(ft_strlen(node_dir->filename) - match.size,
					node_dir->filename + match.size,
					&context->command_line))
		{
			log_error("termcaps_string_to_command_line() failed");
		}
	}
	else
	{
		ft_putstr("\n\r");
		y_diff = 1;
		t_list *pos;
		LIST_FOREACH(&head, pos)
		{
			t_node_dir *node_dir = CONTAINER_OF(pos, t_node_dir, list);

			ft_putstr(node_dir->filename);
			ft_putstr("\n\r");
			y_diff++;
		}
		while (y_diff)
		{
			caps__print_cap(CAPS__UP, 0);
			y_diff--;
		}
	}

	list_dir__destroy(&head);

	return (1);
}

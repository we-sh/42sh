#include "shell.h"
#include <dirent.h>

static void			s_fill_the_match_variable(char **out_path,
									t_buffer *out_match,
									size_t *cmd_size,
									char *cmd)
{
	char		*match;

	match = ft_strrchr(cmd + *cmd_size, '/');
	if (match == NULL)
	{
		*out_path = "./";
		match = cmd + *cmd_size;
		out_match->bytes = match;
		out_match->size = ft_strlen(match);
	}
	else
	{
		*out_path = cmd + *cmd_size;
		ft_memmove(match + 2, match + 1, ft_strlen(match + 1) + 1);
		match[1] = 0;
		match += 2;
		out_match->bytes = match;
		out_match->size = ft_strlen(match);
	}
}

static void			s_get_path_and_match(char **out_path,
									t_buffer *out_match,
									size_t *cmd_size,
									char *cmd)
{
	cmd[*cmd_size] = 0;
	if (*cmd_size == 0 || cmd[*cmd_size - 1] == ' ')
	{
		*out_path = "./";
		out_match->bytes = NULL;
		out_match->size = 0;
		return ;
	}
	while (*cmd_size > 0)
	{
		if (ft_isspace(cmd[*cmd_size]))
		{
			*cmd_size = *cmd_size + 1;
			break ;
		}
		*cmd_size = *cmd_size - 1;
	}
	s_fill_the_match_variable(out_path, out_match, cmd_size, cmd);
}

static int			key__completion_search_match(t_list *head,
												char *path,
												t_buffer *match)
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
		if ((!match->size && ep->d_name[0] == '.') ||
			ft_memcmp(ep->d_name, match->bytes, match->size))
			continue ;
		new = node_dir__create(ep);
		if (!new)
		{
			list_dir__destroy(head);
			return (0);
		}
		list_push_back(&new->list, head);
		if (new->filename_size > ref_size)
			ref_size = new->filename_size;
	}
	ASSERT(!closedir(dp));
	return (ref_size);
}

size_t				key__completion_list_dir(t_termcaps_context *context,
									t_list *head,
									t_buffer *match)
{
	char			*path;
	size_t			cmd_size;
	char			cmd[1024];
	size_t			ref_size;

	if (!command_to_buffer(&context->command,
				sizeof(cmd) - 1,
				&cmd_size,
				cmd))
	{
		log_error("command_to_buffer() failed");
		return (-1);
	}
	s_get_path_and_match(&path, match, &cmd_size, cmd);
	ref_size = key__completion_search_match(head, path, match);
	return (ref_size);
}

#include "shell.h"
#include <dirent.h>

static int	s_get_path_and_match(char **out_path,
								t_buffer *out_match,
								size_t *cmd_size,
								char *cmd)
{
	char		*match;



	cmd[*cmd_size] = 0;

	if (*cmd_size == 0 || cmd[*cmd_size - 1] == ' ')
	{
		*out_path = "./";
		out_match->bytes = NULL;
		out_match->size = 0;
		return (1);
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
	return (1);
}
size_t		key__completion_list_dir(t_termcaps_context *context,
									t_list *head,
									t_buffer *match)
{

	char			*path;
	size_t		cmd_size;
	char		cmd[1024];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(cmd) - 1,
				&cmd_size,
				cmd))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (-1);
	}

	ASSERT(s_get_path_and_match(&path, match, &cmd_size, cmd));



			log_success("(*match).bytes : %s", (*match).bytes);
			log_success("PATH : %s", path);

	DIR				*dp;
	struct dirent	*ep;
	t_node_dir		*new;
	size_t			ref_size;


	INIT_LIST_HEAD(head);
	if ((dp = opendir(path)) == NULL)
	{
		log_error("opendir() failed");
		return (0);
	}
	ref_size = 0;
	while ((ep = readdir(dp)) != NULL)
	{
		if ((!(*match).size && ep->d_name[0] == '.') ||
			ft_memcmp(ep->d_name, (*match).bytes, (*match).size))
		{
			log_warn("ep->d_name[0] : %s", ep->d_name);
			log_success("(*match).bytes : %s", (*match).bytes);
			log_success("(*match).size : %u", (*match).size);

			continue ;
		}
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
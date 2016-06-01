#include "shell.h"
#include <dirent.h>

void	s_list_dir(const char *path,
		const size_t match_size,
		const char *match,
		int *out_nb_lines)
{
	DIR				*dp;
	struct dirent	*ep;
	int				nb_lines;

	log_debug("path %s match %s match_size %zu", path ? path : "Null", match ? match : "Null", match_size);
	*out_nb_lines = 0;
	dp = opendir(path);
	if (dp != NULL)
	{
		caps__print_cap(CAPS__DOWN, 0);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		nb_lines = 1;
		while ((ep = readdir(dp)) != NULL)
		{
			if (!ft_memcmp(ep->d_name, ".", sizeof(".")) || !ft_memcmp(ep->d_name, "..", sizeof("..")))
				continue ;
			log_debug("ep->d_name %s", ep->d_name);
			if (!ft_memcmp(ep->d_name, match, match_size))
			{
				ft_putstr(ep->d_name);
				caps__print_cap(CAPS__DOWN, 0);
				caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
				nb_lines++;
			}
		}
		if (closedir(dp) != 0)
			log_error("closedir() failed");
		*out_nb_lines = nb_lines;
	}
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
		path = NULL;
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

	s_list_dir(path, match.size, match.bytes,  &y_diff);

	while (y_diff)
	{
		caps__print_cap(CAPS__UP, 0);
		y_diff--;
	}
	caps__print_cap(CAPS__CARRIAGE_RETURN, 0);

	return (1);
}

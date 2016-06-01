#include "shell.h"
#include <dirent.h>

void	s_list_dir(const char *dirname, int *out_nb_lines)
{
	DIR				*dir;
	struct dirent	*ep;
	int				nb_lines;

	*out_nb_lines = 0;
	if (dirname == NULL)
	{
		log_error("dirname %p", (void *)dirname);
		return ;
	}
	nb_lines = 0;
	dp = opendir(dirname);
	if (dp != NULL)
	{
		caps__print_cap(CAPS__DOWN, 0);
		caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		nb_lines++;
		while ((ep = readdir(dp)) != NULL)
		{
			if (ep->d_name != NULL)
			{
				ft_putstr(ep->d_name);
				caps__print_cap(CAPS__DOWN, 0);
				caps__print_cap(CAPS__CARRIAGE_RETURN);
				nb_lines++;
			}
		}
		if (closedir(dp) != 0)
			log_error("closedir() failed");
	}
	*out_nb_lines = nb_lines;
}

int		key__completion(t_internal_context *context)
{
	size_t	cmd_size;
	char	cmd[2048];
	int		x_old, y_old, y_diff;

	if (!caps__cursor_getxy(&x_old, &y_old))
	{
		log_error("caps__cursor_getxy() failed");
		return (-1);
	}

	/*
	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(cmd),
				&cmd_size,
				cmd))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (-1);
	}
	*/

	s_list_dir("./", &y_diff);

	if (!caps__cursor_setxy(x_old, y_old - y_diff))
	{
		log_fatal("caps__cursor_setxy() failed");
		return (-1);
	}

	return (1);
}

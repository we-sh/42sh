#include "shell.h"

int					stdin_loop(t_sh *sh)
{
	char			*input;
	int				ret;
	bool			end_of_file;

	end_of_file = 1;
	input = NULL;
	while (1)
	{
		if (sh->is_interactive == true)
			input = termcaps_read_input(sh->fd);
		else
			end_of_file = get_next_line(sh->fd, &input);
		if (input == NULL || end_of_file == 0)
		{
			log_info("termcqps_reqd_input() returned NULL");
			break ;
		}
		ret = parse(sh, input);
		if (ret != ST_OK)
		{
			if (ret == ST_EXIT)
				return (ST_OK);
			display_status(ret, NULL, NULL);
			return (-1);
		}
		ft_strdel(&input);
		input = NULL;
	}

	return (ST_END_OF_INPUT);
}

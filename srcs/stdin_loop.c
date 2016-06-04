#include "shell.h"

int					stdin_loop(t_sh *sh)
{
	char			*input;
	int 			ret;

	input = NULL;
	while (1)
	{
		input = termcaps_read_input(sh->fd);
		if (input == NULL)
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
		if (!sh->is_interactive)
			break ;
	}

	return (ST_END_OF_INPUT);
}

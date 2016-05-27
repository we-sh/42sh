#include "shell.h"

int					stdin_loop(t_sh *sh)
{
	char			*input;

	input = NULL;
	while (1)
	{
		input = termcaps_read_input(sh->fd);
		if (input == NULL)
		{
			log_info("termcaps_read_input() failed");
			break ;
		}
		if (!ft_strcmp(input, "exit"))//temporaire
		{
			log_info("exit");
			break ;
		}
		parse(sh, input);
		ft_strdel(&input);
		input = NULL;
	}

	return (ST_END_OF_INPUT);
}

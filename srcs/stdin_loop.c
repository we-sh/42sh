#include "shell.h"

int					stdin_loop(t_sh *sh)
{
	char			*input;
	int 			exit_status;

	input = NULL;
	while (1)
	{
		input = termcaps_read_input(sh->fd);
		if (input == NULL)
			continue ;
		if (!ft_strcmp(input, "exit"))//temporaire
		{
			log_info("exit");
			break ;
		}
		exit_status = parse(sh, input);
		if (exit_status != ST_OK)
		{
			log_status(exit_status, NULL);
			return (-1);
		}
		ft_strdel(&input);
		input = NULL;
	}

	return (ST_END_OF_INPUT);
}

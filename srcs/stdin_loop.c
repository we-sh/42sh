#include "shell.h"

int					stdin_loop(void)
{
	char			*input;
	struct termios	*termios_old;

	input = NULL;
	while (1)
	{
		input = termcaps_read_input(shell_fd());
		if (input == NULL)
		{
			log_info("termcaps_read_input() failed");
			break ;
		}
		if (!ft_strcmp(input, "exit"))//temporaire
		{
			log_info("exit");
			termios_old = termcaps_old_termios();
			if (termios_old == NULL)
				log_error("termcaps_old_termios() failed");
			else if (tcsetattr(shell_fd(), TCSADRAIN, termios_old) != 0)
				log_error("tcsetattr() failed t finalize, restart your terminal");
			exit(0);
		}
		parse(input);
		ft_strdel(&input);
		input = NULL;
	}

	return (ST_END_OF_INPUT);
}

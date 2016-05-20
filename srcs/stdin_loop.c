#include "shell.h"

int					stdin_loop(void)
{
	char			*input;
	struct termios	termios_old;

	input = NULL;
	while (1)
	{
		input = termcaps_read_input(shell_fd());
		if (input == NULL)
		{
			log_info("input null");
			break ;
		}
		if (!ft_strcmp(input, "exit"))//temporaire
		{
			log_info("exit\n");
			termios_old = termcaps_old_termios();
			if (tcsetattr(shell_fd(), TCSADRAIN, &termios_old) != 0)
				FATAL("tcsetattr() failed t finalize %s\r", "");
			exit(0);
		}
		parse(input);
		ft_strdel(&input);
		input = NULL;
	}

	return (ST_END_OF_INPUT);
}

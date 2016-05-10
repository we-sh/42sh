#include "shell.h"

int	stdin_loop(void)
{
	char	*input;
	int		r;

	while (1)
	{
		ft_putstr(PS1_DFLT);
		if ((r = get_next_line(STDIN_FILENO, &input)) < 1)
			break ;
		log_debug("input: |%s|\n", input);
		ft_strdel(&input);
	}
	return (r != 0) ? ST_READ : ST_END_OF_INPUT;
}

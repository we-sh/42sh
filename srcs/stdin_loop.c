#include "shell.h"

int	stdin_loop(void)
{
	char	*input;
	int		sh_is_inter;
	int		r;

	sh_is_inter = (isatty(STDIN_FILENO)) ? 1 : 0;
	while (1)
	{
		if (sh_is_inter)
			ft_putstr(PS1_DFLT);
		if ((r = get_next_line(STDIN_FILENO, &input)) < 1)
			break ;
		log_debug("input: |%s|\n", input);
		parse(input);
		ft_strdel(&input);
	}
	return (r != 0) ? ST_READ : ST_END_OF_INPUT;
}

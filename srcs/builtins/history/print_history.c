#include "shell.h"

void	print_history(t_sh *sh, t_proc *p)
{
	int		i;

	i = 1;
	while (i < p->argc)
	{
		termcaps_write(sh->fd, p->argv[i], ft_strlen(p->argv[i]));
		termcaps_write(sh->fd, "\n", sizeof("\n") - 1);
		i++;
	}
}

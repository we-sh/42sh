#include "shell.h"
#include "builtin_echo.h"

static int	s_exec(t_proc *p)
{
	int		i;

	i = 1;
	while (p->argv[i])
	{
		if (option_is_set(&p->bltin_opt_head, ST_BLTIN_ECHO_OPT_O) == 1)
			ft_putstr(builtin_echo_escape(p->argv[i]));
		else
			ft_putstr(p->argv[i]);
		if (i + 1 < p->argc)
			ft_putchar(' ');
		i++;
	}
	if (option_is_set(&p->bltin_opt_head, ST_BLTIN_ECHO_OPT_N) == 0)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

int			builtin_echo(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	(void)builtin;
	(void)sh;
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(p));
	return (ST_OK);
}

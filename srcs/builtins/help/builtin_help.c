#include "shell.h"

static int	s_before(t_proc *p)
{
	int	i;
	int	exists;

	if (p->argc != 2)
		p->builtin_status = p->argc > 2 ? ST_E2BIG : ST_EINVAL;
	else
	{
		exists = 0;
		i = BLTIN_NONE;
		while (++i < BLTIN_TOTAL)
		{
			if (ft_strcmp(p->argv[1], g_builtins[i]->name) == 0)
			{
				p->builtin_status = -i;
				exists = 1;
				break;
			}
		}
		if (exists == 0)
			p->builtin_status = ST_EINVAL;
	}
	return (ST_OK);
}

static int	s_exec(t_proc *p)
{
	if (p->builtin_status > ST_OK)
	{
		// todo use `log_status()` instead
		ft_putendl_fd(i18n_translate(p->builtin_status), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putstr(g_builtins[-p->builtin_status]->name);
	ft_putstr(": ");
	ft_putendl(g_builtins[-p->builtin_status]->usage);
	ft_putendl(i18n_translate(g_builtins[-p->builtin_status]->description));
	return (EXIT_SUCCESS);
}

int			builtin_help(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	(void)builtin;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(p));
	return (ST_OK);
}

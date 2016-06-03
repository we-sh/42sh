#include "shell.h"

static int	s_before(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 2)
			p->bltin_status = ST_E2BIG;
		else if (p->argc == 2)
		{
			if (ft_strisnumeric(p->argv[1]) == 0)
				p->bltin_status = ST_EINVAL;
			else
				p->bltin_status = -((unsigned char)ft_atoi(p->argv[1]));
		}
	}
	return (ST_OK);
}

static int	s_exec(t_sh *sh, t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status > ST_OK)
	{
		// todo use `log_status()` instead
		ft_putendl_fd(i18n_translate(p->bltin_status), STDERR_FILENO);
		if (p->bltin_status == ST_EINVAL)
		{
			ft_putstr_fd(i18n_translate(ST_USAGE), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(builtin->usage, STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	if (p->bltin_status < ST_OK)
		return (-p->bltin_status);
	else if (p->bltin_status == ST_OK && p->argc == 2)
		return (EXIT_SUCCESS);
	return (sh->last_exit_status);
}

static int	s_after(t_proc *p)
{
	if (p->bltin_status == ST_OK)
		return (ST_EXIT);
	return (ST_OK);
}

int			builtin_exit(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(p));
	return (ST_OK);
}

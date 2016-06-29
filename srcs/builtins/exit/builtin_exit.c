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
				p->bltin_status = ST_NAN;
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
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_SUCCESS);
	}
	if (p->bltin_status < ST_OK)
		return (-p->bltin_status);
	else if (p->bltin_status == ST_OK && p->argc == 2)
		return (EXIT_SUCCESS);
	else if (p->bltin_status == ST_E2BIG)
		return (EXIT_FAILURE);
	return (sh->last_exit_status);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	if (p->bltin_status == ST_E2BIG)
		return (ST_OK);
	if (p->bltin_status > ST_OK)
		sh->last_exit_status = EXIT_FAILURE;
	ft_putendl_fd("exit", STDERR_FILENO);
	return (ST_EXIT);
}

int			builtin_exit(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

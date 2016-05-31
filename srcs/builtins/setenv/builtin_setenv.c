#include "shell.h"


static int	s_before(t_proc *p)
{
	int		ret;

	ret = 0;
	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 1)
		{
			if (p->argc > 3)
				p->bltin_status = ST_E2BIG;
			else if (((ret  = setenv_argv_is_valid(p)) != ST_OK))
				p->bltin_status = ret;
			else
				p->bltin_status = 2;
		}
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p, t_sh *sh)
{
	int		i;

	i = 0;
	if (p->bltin_status == ST_OK)
	{
		while (sh->envp[i])
		{
			ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
			i++;
		}
	}
	else if (p->bltin_status != ST_OK && p->bltin_status != 2)
	{
		ft_putendl_fd(i18n_translate(p->bltin_status), STDERR_FILENO);
		if (p->bltin_status == ST_EINVAL)
		{
			ft_putstr_fd(i18n_translate(ST_USAGE), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(builtin->usage, STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{

	if (p->bltin_status == 2)
		setenv_set_variable_and_value(sh, p);
	p->bltin_status = ST_OK;
	return (ST_OK);
}

int			builtin_setenv(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p, sh));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

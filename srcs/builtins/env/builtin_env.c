#include "shell.h"

static int	s_before(t_proc *p)
{
	int		ret;

	ret = 0;
	if (p->bltin_status == ST_OK)
	{
		if (p->argc == 0)
			p->bltin_status = ST_OK;
		if ((ret = option_is_set(&p->bltin_opt_head, ST_BLTIN_ENV_OPT_I)) == 1)
			p->bltin_status = ST_BLTIN_ENV_OPT_I;
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
	else if (p->bltin_status == ST_BLTIN_ENV_OPT_I)
	{
		ft_memdel_tab((void ***)&sh->envp);
		sh->envp = NULL;
		ft_array_pop(&p->argv, 0, 1);
		execve(p->argv[0], p->argv, sh->envp);
	}
	else if (p->bltin_status != ST_OK && p->bltin_status != ST_BLTIN_ENV_OPT_I)
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

static int	s_after(t_proc *p)
{
	(void)p;
	return (ST_OK);
}

int			builtin_env(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		return(s_exec(builtin, p, sh));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(p));
	return (ST_OK);
}

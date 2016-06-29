#include "shell.h"

static int	s_before(t_proc *p)
{
	int		ret;

	ret = 0;
	if (p->bltin_status == ST_OK)
	{
		if (p->argc == 1)
			p->bltin_status = ST_E2SMALL;
		else
			p->bltin_status = ST_OK;
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status != ST_OK)
	{
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	int		i;

	i = 1;
	if (p->bltin_status == ST_OK)
	{
		while (p->argv[i])
		{
			env_unset(&sh->envp, p->argv[i]);
			if (ft_strcmp(p->argv[i], "PATH") == 0)
			{
				path_free_hasht();
				path_init_hasht(sh->envp);
			}
			i++;
		}
	}
	return (ST_OK);
}

int			builtin_unsetenv(t_builtin const *builtin,
								int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

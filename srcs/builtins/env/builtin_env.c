#include "shell.h"

static int	s_before(t_proc *p)
{
	(void)p;
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p, t_sh *sh)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (p->bltin_status == ST_OK)
	{
		if ((ret = option_is_set(&p->bltin_opt_head, ST_BLTIN_ENV_OPT_I)) == 1)
		{	
			ft_memdel_tab((void ***)&sh->envp);
			sh->envp = NULL;
		}
		// USE JM FUNCTION TO POP ENV VARIABLE TEST=TOTO
		if (p->argc == 1)
		{
			while (sh->envp[i])
			{
				ft_putendl_fd(sh->envp[i], STDOUT_FILENO);
				i++;
			}			
		}
		else
			ft_array_pop(&p->argv, 0, 1);
	}
	else if (p->bltin_status != ST_OK)
	{
		builtin_usage(builtin, p->bltin_status);
		exit(EXIT_FAILURE);
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

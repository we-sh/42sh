#include "shell.h"

static int	s_exec_display(t_proc *p)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if ((ret = option_is_set(&p->bltin_opt_head, ST_BLTIN_ENV_OPT_I)) == 1)
	{
		ft_memdel_tab((void ***)&p->envp);
		if ((p->envp = (char **)malloc(sizeof(char *) * 1)) == NULL)
			return (ST_MALLOC);
		p->envp[0] = NULL;
	}
	p->argc--;
	ft_array_pop(&p->argv, 0, 1);
	env_or_var_update_from_cmd_line(&p, NULL);
	if (p->argc == 0)
	{
		while (p->envp[i])
		{
			ft_putendl_fd(p->envp[i], STDOUT_FILENO);
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	return (ST_OK);
}

static int	s_before(t_proc *p)
{
	(void)p;
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status == ST_OK)
		s_exec_display(p);
	else
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

int			builtin_env(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		return (s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(p));
	return (ST_OK);
}

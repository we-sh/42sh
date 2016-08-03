#include "shell.h"
#include "builtin_set_local.h"

static int	s_exec_display(t_proc *p)
{
	int		i;

	i = 0;
	if (p->argc == 1)
		p->argc--;
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


static int	s_before(t_sh *sh, t_proc *p)
{
	char	*tmp;
	char	*tmp2;
	char	*value;
	int		i;

	i = 1;
	tmp = NULL;
	if (p->bltin_status == ST_OK)
	{
		while(p->argv[i])
		{
			if ((tmp = ft_strdup(p->argv[i])) == NULL)
				return (ST_MALLOC);
			if ((tmp2 = ft_strdup(p->argv[i])) == NULL)
				return (ST_MALLOC);
			if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
				builtin_local_var_set_local_loop(&sh, tmp2);
			free(tmp);
			free(tmp2);
			i++;
		}
	}
	return (ST_OK);
}

static int	s_exec(t_sh *sh, t_builtin const *builtin, t_proc *p)
{
	int ret;
	t_var *ptr;

	ret = 0;
	ptr = sh->local_vars;
	if (p->bltin_status == ST_OK)
	{
		if ((ret = option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_P)) == 1
			&& p->argc == 1)
			s_exec_display(p);
		else if (p->argc == 1)
			s_exec_display(p);
	}
	else
	{
		builtin_usage(builtin, p->bltin_status);
		exit(EXIT_FAILURE);
	}
	return (ST_OK);
}

static int	s_builtin_export_n_option(t_sh **sh, t_proc *p)
{
	char *value;
	char *tmp;
	int i;
	
	i = 1;
	while (p->argv[i])
	{
		if ((tmp = ft_strdup(p->argv[i])) == NULL)
			return (ST_MALLOC);
		if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
			env_unset(&(*sh)->envp, tmp);
		else
			env_unset(&(*sh)->envp, p->argv[i]);
		free(tmp);
		i++;
	}
	return (ST_OK);
}

static int s_builtin_export_set(t_sh **sh, t_proc *p)
{
	char *value;
	char *tmp;
	int ret;
	int i;

	i = 1;
	ret = 0;
	while (p->argv[i])
	{
		if ((value = local_var_register(*sh, p->argv[i])) != NULL)
		{
			if ((tmp = ft_strjoin3_safe(p->argv[i],"=",value)) == NULL)
				return (ST_MALLOC);
			if ((builtin_local_var_set_local_loop(sh, tmp)) == ST_MALLOC)
				return (ST_MALLOC);
			if ((ret = env_set(&(*sh)->envp, p->argv[i], value)) != ST_OK)
				return (ret);
			free(tmp);
		}
		else
		{
			if ((tmp = ft_strdup(p->argv[i])) == NULL)
				return (ST_MALLOC);
			if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
			{
				if ((builtin_local_var_set_local_loop(sh, p->argv[i])) == ST_MALLOC)
					return (ST_MALLOC);
				if ((ret = env_set(&(*sh)->envp, tmp, value)) != ST_OK)
					return (ret);
			}
			free(tmp);
		}
		i++;
	}
	return (ST_OK);
}

static int	s_after(t_sh **sh, t_proc *p)
{
	int i;

	i = 1;
	if (p->bltin_status == ST_OK)
	{
		if ((option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_N)) == 1)
		{
			if ((s_builtin_export_n_option(sh, p)) == ST_MALLOC)
				return (ST_MALLOC);
		}
		else
		{
			if ((s_builtin_export_set(sh, p)) == ST_MALLOC)
				return (ST_MALLOC);
		}
	}
	return (ST_OK);
}

int			builtin_export(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit (s_exec(sh, builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}

#include "shell.h"
#include "builtin_set_local.h"

static int	s_exec_display(t_sh *sh, t_proc *p)
{
	int		i;
	t_var	*ptrvar;

	ptrvar = sh->local_vars;
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
		i = 0;
		while (ptrvar != NULL)
		{
			ft_putstr_fd(ptrvar->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			if (ptrvar->value)
				ft_putendl_fd(ptrvar->value, STDOUT_FILENO);
			else
				ft_putendl_fd("\0", STDOUT_FILENO);
			ptrvar = ptrvar->next;
		}
		exit(EXIT_SUCCESS);
	}
	return (ST_OK);
}


static int	s_before(t_sh *sh, t_proc *p)
{
	char	*tmp;
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
			if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
				builtin_local_var_set_local_loop(&sh, tmp, value);
			else if (tmp[0] != '$')
				builtin_local_var_add(&sh, tmp, value);
			free(tmp);
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
			s_exec_display(sh, p);
		else if (p->argc == 1)
			s_exec_display(sh, p);
	}
	else
	{
		builtin_usage(builtin, p->bltin_status);
		exit(EXIT_FAILURE);
	}
	return (ST_OK);
}

static int	s_after(t_sh **sh, t_proc *p)
{
	int i;

	i = 1;
	if (p->bltin_status == ST_OK)
	{
		while (p->argv[i])
		{
			if ((option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_N)) == 1)
			{
				if ((builtin_export_n_option(sh, p->argv[i])) == ST_MALLOC)
					return (ST_MALLOC);
			}
			else
			{
				if ((builtin_export_set(sh, p->argv[i])) == ST_MALLOC)
					return (ST_MALLOC);
			}
			i++;
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

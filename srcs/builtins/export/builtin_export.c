#include "shell.h"
#include "builtin_set_local.h"

static int	s_check_argv_validity(t_proc *p, int flag, int *index)
{
	char	*tmp;
	int		ret;

	if ((tmp = ft_strdup(p->argv[*index])) == NULL)
		return (ST_MALLOC);
	env_get_value_and_remove_equal_sign(tmp);
	if ((ret = setenv_argv_is_valid(tmp)) != ST_OK)
	{
		if (flag == BLTIN_CB_EXEC)
			display_status(ST_BLTIN_SETENV_INVALID_IDENTIFIER, p->argv[*index], NULL);
		*index += 1;
		free(tmp);
		return (ST_DONE);
	}
	free(tmp);
	return (ST_OK);
}

static void	s_display_and_usage(t_sh *sh, t_proc *p)
{
	if (option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_P) == 1
	&& p->argc == 1
	&& option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_N) == 0)
		builtin_export_display(sh, p);
	else if (p->argc == 1)
		builtin_export_display(sh, p);
}

static int	s_exec(t_sh *sh, t_builtin const *builtin, t_proc *p)
{
	int		ret;
	t_var	*ptr;
	int		i;
	
	i = 0;
	ret = 0;
	ptr = sh->local_vars;
	while (p->argv[i])
	{
		if ((ret = s_check_argv_validity(p, BLTIN_CB_EXEC, &i)) == ST_DONE)
			continue ;
		else if (ret == ST_MALLOC)
			return (ST_MALLOC);
		i++;
	}
	if (p->bltin_status == ST_OK)
		s_display_and_usage(sh, p);
	else
	{
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh **sh, t_proc *p)
{
	int		i;
	int		ret;

	i = 1;
	if (p->bltin_status == ST_OK)
	{
		while (p->argv[i])
		{
			if ((ret = s_check_argv_validity(p, BLTIN_CB_AFTER, &i)) == ST_DONE)
				continue ;
			else if (ret == ST_MALLOC)
				return (ST_MALLOC);
			if (option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_N) == 1
			&& (option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_P)) == 0)
			{
				if ((builtin_export_n_option(sh, p->argv[i])) == ST_MALLOC)
					return (ST_MALLOC);
			}
			else
				if ((builtin_export_set(sh, p, i)) == ST_MALLOC)
					return (ST_MALLOC);
			i++;
		}
	}
	return (ST_OK);
}

int			builtin_export(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (ST_OK);
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}

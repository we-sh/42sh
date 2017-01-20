#include "shell.h"
#include "builtin_set_local.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the local variable struct or if env is found on the
** input. pop all valid variables placed at start of a command line and set them
** into the specified environment.
*/

static int		s_is_valid_name(char *arg)
{
	char	*equal_sign;
	char	old;
	int		is_valid;

	is_valid = -1;
	if ((equal_sign = ft_strstr(arg, "=")) != NULL)
	{
		is_valid = 0;
		old = arg[equal_sign - arg];
		arg[equal_sign - arg] = '\0';
		if (setenv_argv_is_valid(arg) == ST_OK)
			is_valid = 1;
		arg[equal_sign - arg] = old;
	}
	return (is_valid);
}


static int		s_set_tab_return_action(char **argv)
{
	int			add_to_env;
	int			is_valid;

	add_to_env = 0;
	while (*argv != NULL)
	{
		if ((is_valid = s_is_valid_name(*argv)) != 1)
		{
			add_to_env = 1;
			if (is_valid == -1)
				break ;
		}
		else if (is_valid == 0)
			return (0);
		argv++;
	}
	return (add_to_env);
}

static int		s_add_to_local_var(char ***argv, int *argc, t_sh **sh,
									char ***envp)
{
	char		*value;
	int			ret;
	char		*tmp;

	while ((*argv)[0] != NULL && (*argv)[0][0] != '\0' && (*argv)[0][0] != '='
		&& (value = env_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		if ((tmp = ft_strdup(value)) == NULL)
			return (ST_MALLOC);
		if ((ret = expand_tilde_through_buffer(*sh, &tmp)) != ST_OK)
			return (ret);
		if (env_get(*envp, (*argv)[0]) != NULL)
		{
			if ((ret = env_set(&(*sh)->envp, (*argv)[0], tmp)) != ST_OK)
				return (ret);
		}
		else if ((ret = builtin_local_var_set_local_loop(sh, (*argv)[0], tmp))
				!= ST_OK)
			return (ret);
		free(tmp);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

static int		s_add_to_env(t_sh *sh, char ***envp, int *argc, char ***argv)
{
	char		*value;
	int			ret;
	char		*tmp;

	ret = 0;
	value = NULL;
	while ((*argv)[0] != NULL && (*argv)[0][0] != '\0' && (*argv)[0][0] != '='
		&& (value = env_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		if ((tmp = ft_strdup(value)) == NULL)
			return (ST_MALLOC);
		if ((ret = expand_tilde_through_buffer(sh, &tmp)) != ST_OK)
			return (ret);
		if (envp != NULL)
		{
			if ((ret = env_set(envp, (*argv)[0], tmp)) != ST_OK)
				return (ret);
		}
		free(tmp);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

int				env_or_var_update_from_cmd_line(t_proc **p,
											t_sh **sh)
{
	int			ret;
	int			add_to_env;

	if (((*p)->is_subshell == 1) || (&(*p)->argv) == NULL)
		return (ST_OK);
	if ((add_to_env = s_set_tab_return_action((*p)->argv)) == ST_MALLOC)
		return (ST_MALLOC);
	if (add_to_env == 0)
	{
		(*p)->is_valid = 0;
		if ((ret = s_add_to_local_var(&(*p)->argv, &(*p)->argc, sh,
				&(*p)->envp)) != ST_OK)
			return (ret);
	}
	else if (add_to_env == 1)
	{
		if ((ret = s_add_to_env(*sh, &(*p)->envp, &(*p)->argc, &(*p)->argv))
			!= ST_OK)
			return (ret);
	}
	return (ST_OK);
}

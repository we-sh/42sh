#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the local variable struct or if env is found on the input.
** pop all valid variables placed at start of a command line and set them
** into the specified environment.
*/

static int		s_set_tab_return_action(char ***argv, int *argc, char **tmptab)
{
	int			add_to_env;
	int		i;
	int		nbr;

	i= 0;
	add_to_env = 0;
	nbr = *argc;
	while (nbr > 0 && (*argv)[0] != NULL && (*argv)[0][0] != '\0'
		&& *argv[0][0] != '=')
	{
		if (*argv[0] && ft_strcmp(*argv[0], "env") == 0)
			add_to_env = 1;
		if ((tmptab[i] = ft_strdup(*argv[0])) == NULL)
			return (ST_MALLOC);
		i++;
		ft_array_pop(argv, 0, 1);
		nbr--;
	}
	tmptab[i] = NULL;
	return (add_to_env);
}

static int	s_add_to_local_valid(char **test)
{
	char	*value;
	int		i;
	int		add_to_local_var;
	
	i = 0;
	while (test[i] != NULL && test[i][0] != '\0' && test[i][0] != '=')
	{
		if ((value = env_get_value_and_remove_equal_sign(test[i])) != NULL)
			add_to_local_var = 1;
		else
		{
			add_to_local_var = 0;
			break ;
		}
		i++;
	}
	return (add_to_local_var);
}

static int 	s_add_to_local_var(char ***tmptab, int *argc)
{
	char	**test;
	int		add_to_local_var;
	int i;

	add_to_local_var = 0;
	if ((test = (char **)malloc(sizeof(char *)* (*argc + 1))) == NULL)
		return (ST_MALLOC);
	i = 0;
	while ((*tmptab)[i])
	{
		if ((test[i] = ft_strdup((*tmptab)[i])) == NULL)
			return (ST_MALLOC);
		i++;
	}
	test[i] = NULL;
	add_to_local_var = s_add_to_local_valid(test);
	ft_memdel_tab((void ***)&test);
	if (add_to_local_var == 1)
	{
		if ((ft_array_push_front(tmptab, "setlocal")) == -1)
			return (ST_MALLOC);
		*argc += 1;
	}
	return (ST_OK);
}

static int s_add_to_env(char ***envp, int *argc, char ***tmptab)
{
	char	*value;
	int 	ret;

	ret = 0;
	value = NULL;
	while ((*tmptab)[0] != NULL && (*tmptab)[0][0] != '\0' && (*tmptab)[0][0] != '='
		&& (value = env_get_value_and_remove_equal_sign((*tmptab)[0])) != NULL)
	{
		if (envp != NULL)
			if ((ret = env_set(envp, (*tmptab)[0], value)) != ST_OK)
				return (ret);
		*argc -= 1;
		ft_array_pop(tmptab, 0, 1);
	}
	return (ST_OK);
}

int			env_or_var_update_from_cmd_line(char ***argv,
											int *argc,
											char ***envp,
											int loc)
{
	char 	**tmptab;
	int		ret;
	int		add_to_env;

	if (!argv)
		return (ST_OK);
	if ((tmptab = (char **)malloc(sizeof(char *)* (*argc + 1))) == NULL)
		return (ST_MALLOC);
	if ((add_to_env = s_set_tab_return_action(argv, argc, tmptab)) == ST_MALLOC)
		return (ST_MALLOC);
	if (loc == 1)
		add_to_env = 1;
	if (add_to_env == 0)
	{
		if ((ret = s_add_to_local_var(&tmptab, argc)) != ST_OK)
			return (ret);
	}
	else
	{
		if ((ret = s_add_to_env(envp, argc, &tmptab)) != ST_OK)
			return (ret);
	}
	*argv = tmptab;
	return (ST_OK);
}

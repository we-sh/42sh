#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the specified environment.
*/

static char	*s_get_value_and_remove_equal_sign(char *arg)
{
	char	*equal_sign;

	if ((equal_sign = ft_strstr(arg, "=")) != NULL)
	{
		arg[equal_sign - arg] = '\0';
		if (setenv_argv_is_valid(arg) == ST_OK)
			return (equal_sign + 1);
	}
	return (NULL);
}

int			env_update_from_cmd_line(char ***argv, int *argc, char ***envp)
{
	char	*value;
	int		ret;

	if (!argv)
		return (ST_OK);
	while ((*argv)[0] != NULL && (*argv)[0][0] != '\0' && (*argv)[0][0] != '='
		&& (value = s_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		if (envp != NULL)
			if ((ret = env_set(envp, (*argv)[0], value)) != ST_OK)
				return (ret);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

/* PUT IT IN A NEW FILE */

// static int s_add_to_local(t_sh **sh, char *key)
// {
// 	t_var		*ptr;
// 	t_var		*newptr;
// 	char		*value;
// 	char		*tmp;

// 	if ((value = s_get_value_and_remove_equal_sign(key)) != NULL)
// 		tmp = ft_strdup(key);
// 	ptr = (*sh)->local_vars;
// //	head = &(*sh)->local_vars.var_list;
// 	newptr = (t_var *)malloc(sizeof(t_var) + 1);
// 	while (ptr)
// 	{
// 		if (ft_strcmp(ptr->key == ) == 0)
// 		ptr = ptr->next;
// 	}
// 	ptr = newptr;

// 	log_warn("ptr -> %s",ptr->key);
// 	log_warn("value -> %s",ptr->value);
// //		local->key = ft_strdup(key);
// 	return (ST_OK);
// }

static int s_local_is_valid(t_sh *sh, t_job **j, int *i)
{
	char	**test;
	char	*value;

	test = ft_strsplit((*j)->command, ' ');
	while (test[*i] != '\0')
	{
		if (path_hash_finder(sh->envp, &test[*i]) == ST_OK)
			return (-1);
		if ((value = s_get_value_and_remove_equal_sign(test[*i])) == NULL)
			return (-1);
		*i += 1;
	}
	ft_memdel_tab((void ***)&test);
	return (0);
}

int			local_var_insert(t_sh **sh, t_job **j)
{
	char	*tmp;

	i = 0;
	log_info("Value of job %s", (*j)->command);
	if (s_local_is_valid(*sh, j, &i) != ST_OK)
		return (ST_OK);
	tmp = ft_strdup((*j)->command);
	ft_memdel((void **)&((*j)->command));
	(*j)->command = ft_strjoin("setlocal ", tmp);
	log_success("final output :%s",(*j)->command);
	return (0);
}

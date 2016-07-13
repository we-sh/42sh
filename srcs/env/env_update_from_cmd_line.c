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

int local_var_insert(t_sh *sh, t_job **j)
{
	char **tab;

	log_warn("Value of job %s", (*j)->command);
	tab = ft_strplit((*j)->command);
	// while ((*envp)[i] != NULL)
	// {
	// 	log_info("Value of env[%d] : %s", i, (*envp)[i]);
	// 	i++;
	// }
	// i = 0;
	// log_info("Value ARGC : %d", *argc);
	
	// while ((*argv)[i] != NULL && (*argv)[i][0] != '\0' && (*argv)[i][0] != '=')
	// {
	// 	tmp = *argv[i];
	// 	if (path_hash_finder(*envp, &tmp) == ST_OK)
	// 	{
	// 		flag = 1;
	// 		log_success("IS a binary so add to env %s", tmp);
	// 	}
	// 	else
	// 		log_fatal("NOT a binary so add to env %s", tmp);
	// 	log_warn("POS: %d Value of ARGV[%d] : %s", pos, i, tmp);
	// 	i++;
	// }
}
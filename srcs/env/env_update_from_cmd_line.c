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

	while ((value = s_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		env_set(envp, (*argv)[0], value);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

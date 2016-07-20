#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the specified environment.
*/

int			env_update_from_cmd_line(char ***argv, int *argc, char ***envp)
{
	char	*value;
	int		ret;

	if (!argv)
		return (ST_OK);
	while ((*argv)[0] != NULL && (*argv)[0][0] != '\0' && (*argv)[0][0] != '='
		&& (value = env_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		if (envp != NULL)
			if ((ret = env_set(envp, (*argv)[0], value)) != ST_OK)
				return (ret);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

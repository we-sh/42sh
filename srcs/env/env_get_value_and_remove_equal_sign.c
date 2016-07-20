#include "shell.h"

char	*env_get_value_and_remove_equal_sign(char *arg)
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
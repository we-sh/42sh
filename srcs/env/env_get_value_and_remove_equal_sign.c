#include "shell.h"

char	*env_get_value_and_remove_equal_sign(char *arg)
{
	char	*equal_sign;
	char	old;

	if ((equal_sign = ft_strstr(arg, "=")) != NULL)
	{
		old = arg[equal_sign - arg];
		arg[equal_sign - arg] = '\0';
		if (setenv_argv_is_valid(arg) == ST_OK)
			return (equal_sign + 1);
		arg[equal_sign - arg] = old;
	}
	return (NULL);
}

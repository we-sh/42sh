#include "shell.h"

int			builtin_local_var_update(t_var *ptrvar, char *local, int *flag)
{
	char	*value;

	value = NULL;
	if (ft_strncmp(ptrvar->key, local, ft_strlen(local)) == 0)
	{
		if ((value = env_get_value_and_remove_equal_sign(local)) != NULL)
		{
			free(ptrvar->value);
			if ((ptrvar->value = ft_strdup(value)) == NULL)
				return (ST_MALLOC);
			*flag = 1;
			return (ST_OK);
		}
	}
	return (-1);
}

#include "shell.h"

int			builtin_local_var_update(t_var **ptrvar, char *value)
{
	if (value)
	{
		free((*ptrvar)->value);
		if (((*ptrvar)->value = ft_strdup(value)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

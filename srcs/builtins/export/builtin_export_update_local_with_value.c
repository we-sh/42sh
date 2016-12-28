#include "shell.h"
#include "builtin_set_local.h"

int			builtin_export_update_local_with_value(t_sh **sh, char *argv,
													char *value)
{
	t_var	*ptrvar;

	ptrvar = (*sh)->local_vars;
	while (ptrvar)
	{
		if (ft_strcmp(ptrvar->key, argv) == 0)
		{
			free(ptrvar->value);
			if (value)
			{
				if ((ptrvar->value = ft_strdup(value)) == NULL)
					return (ST_MALLOC);
			}
			return (ST_OK);
		}
		ptrvar = ptrvar->next;
	}
	if ((builtin_local_var_add(sh, argv, value)) == ST_MALLOC)
		return (ST_MALLOC);
	return (ST_OK);
}

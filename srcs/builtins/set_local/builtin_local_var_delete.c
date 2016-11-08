#include "shell.h"

int			builtin_local_var_delete(t_sh **sh, char *key)
{
	t_var	*ptrvar;

	if (!((*sh)->local_vars))
		return (ST_OK);
	ptrvar = (*sh)->local_vars;
	if (ft_strcmp(ptrvar->key, key) == 0)
	{
		if (ptrvar->next)
			(*sh)->local_vars = ptrvar->next;
		else
			(*sh)->local_vars = NULL;
		free(ptrvar);
		return (ST_OK);
	}
	while (ptrvar->next)
	{
		if (ft_strcmp(ptrvar->next->key, key) == 0)
		{
			ptrvar->next = ptrvar->next->next;
			free(ptrvar->next);
			break ;
		}
		ptrvar = ptrvar->next;
	}
	return (ST_OK);
}
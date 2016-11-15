#include "shell.h"
#include "builtin_set_local.h"

int		builtin_local_var_set_local_loop(t_sh **sh, char *key, char *value)
{
	int			ret;
	t_var		*ptrvar;

	ptrvar = (*sh)->local_vars;
	ret = 0;
	while (ptrvar)
	{
		if (ft_strcmp(ptrvar->key, key) == 0)
		{
			ret = builtin_local_var_update(&ptrvar, value);
			return (ret);
		}
		ptrvar = ptrvar->next;
	}
	if ((builtin_local_var_add(sh, key, value)) == ST_MALLOC)
		return (ST_MALLOC);
	return (ST_OK);
}

#include "shell.h"
#include "builtin_set_local.h"

int		builtin_local_var_set_local_loop(t_sh **sh, char *local)
{
	int			flag;
	int			ret;
	t_var		*ptrvar;

	ptrvar = (*sh)->local_vars;
	ret = 0;
	flag = 0;
	while (ptrvar)
	{
		if ((ret = builtin_local_var_update(ptrvar, local, &flag))
			== ST_OK)
			break ;
		else if (ret == ST_MALLOC)
			return (ret);
		ptrvar = ptrvar->next;
	}
	if (flag == 0)
	{
		if ((builtin_local_var_add(sh, local)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
#include "shell.h"
#include "builtin_set_local.h"

int					builtin_export_set(t_sh **sh, t_proc *p, int pos)
{
	int				ret;
	char			*value;
	char			*argv;
	t_var			*ptrvar;

	ptrvar = (*sh)->local_vars;
	if ((argv = ft_strdup(p->argv[pos])) == NULL)
		return (ST_MALLOC);
	value = env_get_value_and_remove_equal_sign(argv);
	if (!value)
	{
		if ((builtin_export_set_with_no_value(sh, p, argv)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	else
	{
		if ((ret = builtin_export_set_local_and_env(sh,
					p->argv[pos])) != ST_OK)
			return (ret);
	}
	free(argv);
	return (ST_OK);
}

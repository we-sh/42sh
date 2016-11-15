#include "shell.h"
#include "builtin_set_local.h"

static int		s_update_tmpenv_from_local(t_proc *p, char *argv, t_sh **sh)
{
	int			ret;
	int			i;

	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], argv, ft_strlen(argv)) == 0)
		{
			if ((ret = builtin_export_set_local_and_env(sh,
						p->envp[i])) != ST_OK)
				return (ret);
			else
				return (ST_OK);
		}
		i++;
	}
	return (ST_DONE);
}

static int		s_update_env_from_local(t_sh **sh, t_var *ptrvar, char *argv)
{
	int			ret;

	while (ptrvar)
	{
		if (ft_strcmp(ptrvar->key, argv) == 0)
		{
			if ((ret = env_set(&(*sh)->envp, argv, ptrvar->value)) != ST_OK)
				return (ret);
			else
				return (ST_OK);
		}
		ptrvar = ptrvar->next;
	}
	return (ST_DONE);
}

int				builtin_export_set_with_no_value(t_sh **sh,
												t_proc *p,
												char *argv)
{
	t_var		*ptrvar;
	int			ret;

	ptrvar = (*sh)->local_vars;
	if ((ret = s_update_tmpenv_from_local(p, argv, sh)) == ST_MALLOC)
		return (ST_MALLOC);
	else if (ret == ST_OK)
		return (ST_OK);
	if ((ret = s_update_env_from_local(sh, ptrvar, argv)) == ST_MALLOC)
		return (ST_MALLOC);
	else if (ret == ST_OK)
		return (ST_OK);
	if ((ret = builtin_local_var_add(sh, argv, NULL)) == ST_MALLOC)
		return (ST_MALLOC);
	return (ret);
}

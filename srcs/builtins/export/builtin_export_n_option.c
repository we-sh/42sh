#include "shell.h"

int			s_builtin_local_var_delete(t_sh **sh, char *key)
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

int			builtin_export_n_option(t_sh **sh, char *argv)
{
	char	*value;
	char	*tmp;

	if ((tmp = ft_strdup(argv)) == NULL)
		return (ST_MALLOC);
	if ((value = env_get_value_and_remove_equal_sign(tmp)) != NULL)
	{
		env_unset(&(*sh)->envp, tmp);
		s_builtin_local_var_delete(sh, tmp);
	}
	else
	{
		env_unset(&(*sh)->envp, argv);
		s_builtin_local_var_delete(sh, tmp);
	}
	free(tmp);
	return (ST_OK);
}

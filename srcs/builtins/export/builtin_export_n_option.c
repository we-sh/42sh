#include "shell.h"

int						s_builtin_local_var_delete(t_sh **sh, char *key)
{
	t_var				*ptrvar;

	log_success("Inside 1 ");
	if (!((*sh)->local_vars))
		return (ST_OK);
	ptrvar = (*sh)->local_vars;
	log_success("Inside 2: %s ", ptrvar->key);
	if (ft_strcmp(ptrvar->key, key) == 0)
	{
		log_success("Inside 3: %s ", ptrvar->key);
		log_success("Inside 3 next: %s ", ptrvar->next);
		free(ptrvar);
		if (ptrvar->next)
			(*sh)->local_vars = ptrvar->next;
		else
			(*sh)->local_vars = NULL;
		return (ST_OK);
	}
	while (ptrvar->next)
	{
	log_success("Inside 3: %s ", ptrvar->next->key);
		if (ft_strcmp(ptrvar->next->key, key) == 0)
		{
			ptrvar->next = ptrvar->next->next;
			log_success("Remove ptrvar->next: %s", ptrvar->next);
			free(ptrvar->next);
			break;
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
		log_success("Remove TMP2: %s", tmp);
		env_unset(&(*sh)->envp, tmp);
		s_builtin_local_var_delete(sh, tmp);
	}
	else
	{
		log_success("Remove TMP1: %s", tmp);
		env_unset(&(*sh)->envp, argv);
		s_builtin_local_var_delete(sh, tmp);
	}
	free(tmp);
	return (ST_OK);
}
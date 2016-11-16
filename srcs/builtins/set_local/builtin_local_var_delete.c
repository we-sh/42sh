#include "shell.h"

static void	s_delete_first(t_sh *sh, t_var *ptrvar)
{
	free(sh->local_vars->key);
	free(sh->local_vars->value);
	if (ptrvar->next)
		sh->local_vars = ptrvar->next;
	else
		sh->local_vars = NULL;
	free(ptrvar);	
}

void		builtin_local_var_delete(t_sh *sh, char *key)
{
	t_var	*ptrvar;

	if (!(sh->local_vars))
		return ;
	ptrvar = sh->local_vars;
	if (ft_strcmp(ptrvar->key, key) == 0)
	{
		s_delete_first(sh, ptrvar);
		return ;
	}
	while (ptrvar->next)
	{
		if (ft_strcmp(ptrvar->next->key, key) == 0)
		{
			free(ptrvar->next->key);
			free(ptrvar->next->value);
			ptrvar->next = ptrvar->next->next;
			free(ptrvar->next);
			break ;
		}
		ptrvar = ptrvar->next;
	}
	return ;
}

#include "shell.h"

static t_var 			*s_local_var_init(void)
{
	t_var		*newvar;

	newvar = (t_var *)malloc(sizeof(t_var));
	if (!(newvar))
		return (NULL);
	newvar->key = NULL;
	newvar->value = NULL;
	newvar->next = NULL;
	return (newvar);
}

int				builtin_local_var_add(t_sh **sh, char *local)
{
	char		*value;
	t_var 		*newvar;
	t_var 		*ptrvar;

	value = env_get_value_and_remove_equal_sign(local);
	if ((newvar = s_local_var_init()) == NULL)
		return (ST_MALLOC);
	if (!((*sh)->local_vars))
		(*sh)->local_vars = newvar;
	ptrvar = (*sh)->local_vars;
	if (!(newvar) || !newvar)
		return (ST_OK);
	while (ptrvar->next)
		ptrvar = ptrvar->next;
	ptrvar->next = newvar;
	newvar->key = ft_strdup(local);
	newvar->value = ft_strdup(value);
	newvar->next = NULL;
	return (ST_OK);
}

#include "shell.h"

char		*local_var_register(t_sh *sh, char *key)
{
	int		i;
	t_var	*ptr;

	i = 0;
	ptr = sh->local_vars;
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}
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
		{
			log_success("ptr->key:%s, key:%s",ptr->key, key);
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}
#include "shell.h"

static char 	*stock_value_into_stack(int i, char *value, char tmp[i])
{
	int 		j;

	j = 0;
	tmp = value;
	return (tmp);
}

char		*env_get(char **envp, char *key)
{
	int			i;
	int			size;
	char		*tmp;
	int 		nbr;

	i = 0;
	tmp = NULL;
	size = ft_strlen(key);
	while (*envp[i])
	{
		if (ft_strncmp(envp[i], key, size) == 0)
		{
			if (envp[i][size] == '=')
				break;
		}
		i++;
	}
	size++;
	nbr = ft_strlen(&envp[i][size]);
	tmp = stock_value_into_stack(size, &envp[i][size], NULL);
	return (tmp);
}
#include "shell.h"

char		*env_get(char **envp, char *key)
{
	int			i;
	int			size;

	i = 0;
	if (!envp || !key)
		return (NULL);
	size = ft_strlen(key);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, size) == 0)
		{
			if (envp[i][size] == '=')
				break;
		}
		i++;
	}
	if (!envp[i])
		return (NULL);
	size++;
	return (&envp[i][size]);
}

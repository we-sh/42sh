#include "shell.h"

int				env_index_value(char **envp, char *variable)
{
	int			i;
	int			size;

	i = 0;
	size = ft_strlen(variable);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], variable, size) == 0)
		{
			if (!envp[i][size])
				return (-1);
			else if (envp[i][size] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}
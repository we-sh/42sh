#include "shell.h"

static char		**s_env_unset(char **envp, int pos)
{
	char		**tmp;
	int			i;
	int			j;
	int			size;

	i = 0;
	j = 0;
	size = 0;
	while (envp[size])
		size++;
	if ((tmp = (char **)malloc(sizeof(char *) * size)) == NULL)
		return (NULL);
	while (envp[i])
	{
		if (i != pos)
		{
			if ((tmp[j++] = ft_strdup(envp[i++])) == NULL)
				return (NULL);
		}
		else
			i++;
	}
	tmp[j] = NULL;
	ft_memdel_tab((void ***)&envp);
	return (tmp);
}

int				env_unset(char ***envp, char *key)
{
	int			ret;

	if (key && ft_strcmp(key, "PATH") == 0)
	{
		path_free_hasht();
		if ((ret = path_init_hasht(*envp)) != ST_OK)
			return (ret);
	}
	if ((ret = env_index_value(*envp, key)) == -1)
		return (ST_OK);
	else
	{
		if ((*envp = s_env_unset(*envp, ret)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

#include "shell.h"

static	int		s_concat_variable(char **str, int pos, char *key, char *value)
{
	char		*tmp;
	char		*tmp2;

	if ((tmp = ft_strjoin(key, "=")) == NULL)
		return (ST_MALLOC);
	if (!value)
	{
		if ((str[pos] = ft_strdup(tmp)) == NULL)
			return (ST_MALLOC);
		free(tmp);	
	}
	else if (value)
	{
		if ((tmp2 = ft_strjoin(tmp, value)) == NULL)
			return (ST_MALLOC);
		free(tmp);
		if ((str[pos] = ft_strdup(tmp2)) == NULL)
			return (ST_MALLOC);
		free(tmp2);
	}
	return (ST_OK);
}

static	char	**s_env_set_new_variable(char **envp, char *variable, char *value)
{
	char		**tmp;
	int			i;
	int			size;

	i = 0;
	size = 0;
	while (envp[size])
		size++;
	if ((tmp = (char **)malloc(sizeof(char *) * (size + 2))) == NULL)
		return (NULL);
	while (envp[i] != NULL)
	{
		if ((tmp[i] = ft_strdup(envp[i])) == NULL)
			return (NULL);
		i++;
	}
	if (s_concat_variable(tmp, i, variable, value) != ST_OK)
		return (NULL);
	i++;
	tmp[i] = NULL;
	ft_memdel_tab((void ***)&envp);
	return (tmp);
}

int				env_set(char ***envp, char *key, char *value)
{
	int			i;
	int			ret;

	i = 0;
	if (!*envp)
	{
		if ((*envp = (char **)malloc(sizeof(char *) * 1)) == NULL)
			return (ST_MALLOC);
		*envp[0] = NULL; 
	}
	if ((ret = env_index_value(*envp, key)) == -1)
	{
		if ((*envp = s_env_set_new_variable(*envp, key, value)) == NULL)
			return (ST_MALLOC);
	}
	else
	{
		if (!value)
		{
			if (s_concat_variable(*envp, ret, key, NULL) != ST_OK)
				return (ST_MALLOC);
		}
		else if (value)
		{
			if (s_concat_variable(*envp, ret, key, value) != ST_OK)
				return (ST_MALLOC);
		}
	}
	return (ST_OK);
}
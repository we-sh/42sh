#include "shell.h"

static	int		s_concat_variable(char **str, int pos, char *key, char *value)
{
	char		*tmp;
	char		*tmp2;

	if (str[pos])
		free(str[pos]);
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

static	char	**s_env_set_new_variable(char **envp, char *var, char *val)
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
	tmp[i] = NULL;
	if (s_concat_variable(tmp, i, var, val) != ST_OK)
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
		(*envp)[0] = NULL;
	}
	if ((ret = env_index_value(*envp, key)) == -1)
	{
		ret = ST_OK;
		if ((*envp = s_env_set_new_variable(*envp, key, value)) == NULL)
			return (ST_MALLOC);
	}
	else
		ret = s_concat_variable(*envp, ret, key, value);
	if (key && ft_strcmp(key, "PATH") == 0)
	{
		path_free_hasht();
		if ((ret = path_init_hasht(*envp)) != ST_OK)
			return (ST_MALLOC);
	}
	return (ret);
}

#include "shell.h"

static	int		s_concat_variable(char **str, int pos, char *key, char *value)
{
	char		*tmp;
	char		*tmp2;
//CHECK DES RETURN ST_MALLOC
	tmp = ft_strjoin(key, "=");
	if (!value)
	{
		str[pos] = ft_strdup(tmp);
		free(tmp);	
	}
	else if (value)
	{
		tmp2 = ft_strjoin(tmp, value);
		free(tmp);
		str[pos] = ft_strdup(tmp2);
		free(tmp2);
	}
	return (ST_OK);
}

static	char	**s_env_set_new_variable(char **envp, char *variable, char *value)
{
	char		**tmp;
	int			i;
	int			size;
//CHECK DES RETURN ST_MALLOC
	i = 0;
	size = 0;
	while (envp[size])
		size++;
	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	s_concat_variable(tmp, i, variable, value);
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
	if ((ret = env_index_value(*envp, key)) == -1)
		*envp = s_env_set_new_variable(*envp, key, value);
	else
	{
		if (!value)
			s_concat_variable(*envp, ret, key, NULL);
		else if (value)
			s_concat_variable(*envp, ret, key, value);
	}
	return (ST_OK); //check other function return
}
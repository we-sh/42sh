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
 
int	env_unset(char ***envp, char *argv)
{
	int		ret;

	if ((ret = env_index_value(*envp, argv)) == -1)
		return (ST_OK); //I don't care Bro
	else
	{
		if ((*envp = s_env_unset(*envp, ret)) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}
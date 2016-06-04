#include "shell.h"


static char		**s_env_unset(char **envp, int pos)
{
	char		**tmp;
	int			i;
	int			j;
	int			size;
//CHECK DES RETURN ST_MALLOC
	i = 0;
	j = 0;
	size = 0;
	while (envp[size])
		size++;
	//	printf("yo \n");
	//printf("key: %s value: %s\n", key, value);//debug

	tmp = (char **)malloc(sizeof(char *) * size);
	while (envp[i])
	{
		if (i != pos)
			tmp[j++] = ft_strdup(envp[i++]);
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
		*envp = s_env_unset(*envp, ret);
	return (ST_OK);
}
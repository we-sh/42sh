#include "shell.h"

int	path_get_new_cmd(char **commande, char *name, char *path)
{
	char	*tmp;
	char	*tmp2;

	if ((tmp = ft_strjoin("/", name)) == NULL)
		return (ST_MALLOC);
	if ((tmp2 = ft_strjoin(path, tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	free(*commande);
	if ((*commande = ft_strdup(tmp2)) == NULL)
		return (ST_MALLOC);
	free(tmp2);
	return (ST_OK);
}

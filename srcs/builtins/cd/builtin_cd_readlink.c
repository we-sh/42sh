#include "shell.h"

int			builtin_cd_readlink(char const *path, char **buf)
{
	char	*current;

	if ((current = getcwd(NULL, 0)) == NULL)
		return (ST_GETCWD);
	if (chdir(path) < 0)
		return (ST_CHDIR);
	ft_memdel((void *)&(*buf));
	if ((*buf = getcwd(NULL, 0)) == NULL)
		return (ST_GETCWD);
	if (chdir(current) < 0)
		return (ST_CHDIR);
	ft_memdel((void *)&current);
	return (ST_OK);
}

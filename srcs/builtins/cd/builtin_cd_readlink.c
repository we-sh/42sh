#include "shell.h"

int			builtin_cd_readlink(char const *path, char **buf)
{
	char	*current;
	int		status;

	status = ST_OK;
	if ((current = getcwd(NULL, 0)) == NULL)
		status = ST_GETCWD;
	else if (chdir(path) < 0)
		status = ST_ENOENT;
	else
	{
		ft_memdel((void *)&(*buf));
		if ((*buf = getcwd(NULL, 0)) == NULL)
			status = ST_GETCWD;
		if (chdir(current) < 0)
			status = ST_CHDIR;
	}
	ft_memdel((void *)&current);
	return (status);
}

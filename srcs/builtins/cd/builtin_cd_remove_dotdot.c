#include "shell.h"
#include "builtin_cd.h"

char				*builtin_cd_remove_dotdot(char *path)
{
	size_t				i;
	char				*tmp;

	i = 0;
	while (path[i] != '\0')
		if (path[i] == '.' && path[i + 1] == '.'
			&& (path[i + 2] == '/' || path[i + 2] == '\0'))
		{
			tmp = path + i + 2;
			if (i > 1)
			{
				i -= 2;
				while (i > 0 && path[i] != '/')
					i--;
			}
			if (i <= 0)
				i = 1;
			path[i] = '\0';
			path = ft_strcat(path, tmp);
		}
		else if (path[i] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0'))
		{
			tmp = path + i + (path[i + 1] == '\0' ? 1 : 2);
			path[i] = '\0';
			path = ft_strcat(path, tmp);
		}
		else
			i++;
	return (path);
}

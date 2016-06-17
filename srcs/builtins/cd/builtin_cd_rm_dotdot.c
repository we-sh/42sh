#include "shell.h"
#include "builtin_cd.h"

static void			s_dot(size_t *i, char **tmp, char **path)
{
	*tmp = *path + *i + ((*path)[*i + 1] == '\0' || (*path)[*i + 1] == '/' ? 1 : 2);
	(*path)[*i] = '\0';
	*path = ft_strcat(*path, *tmp);
}

static void			s_dotdot(size_t *i, char **tmp, char **path)
{
	*tmp = *path + *i + 2;
	if (*i > 1)
	{
		*i -= 2;
		while (*i > 0 && (*path)[*i] != '/')
			(*i)--;
	}
	if (*i <= 0)
		*i = 1;
	(*path)[*i] = '\0';
	*path = ft_strcat(*path, *tmp);
}

char				*builtin_cd_rm_dotdot(char *path)
{
	size_t			i;
	char			*tmp;

	i = 0;
	while (path[i] != '\0')
	{
		if (i > 0 && path[i] == '/' && (path[i + 1] == '\0'
			|| path[i + 1] == '/' || (path[i + 1] == '.' && path[i + 2] == '\0')
			|| (path[i + 1] == '.' && path[i + 2] == '/')))
			s_dot(&i, &tmp, &path);
		else if (path[i] == '.' && path[i + 1] == '.'
			&& (path[i + 2] == '/' || path[i + 2] == '\0'))
			s_dotdot(&i, &tmp, &path);
		else if (path[i] == '.' && (path[i + 1] == '/' || path[i + 1] == '\0'))
		{
			tmp = path + i + (path[i + 1] == '\0' ? 1 : 2);
			path[i] = '\0';
			path = ft_strcat(path, tmp);
		}
		else
			i++;
	}
	return (path);
}

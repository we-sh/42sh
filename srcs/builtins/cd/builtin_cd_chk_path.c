#include "shell.h"
#include "builtin_cd.h"

// todo
#include <sys/stat.h>
typedef struct stat					t_stat;

static int			builtin_cd_checkpath_element(char *path, char **t,
						int i, int follow_lnk)
{
	t_stat				stat;
	int					status;

	if (i > 0)
		path = ft_strcat(path, "/");
	path = ft_strcat(path, t[i]);
	status = ST_OK;
	if (access(path, F_OK) == -1)
		status = ST_ENOENT;
	else if (access(path, X_OK) == -1)
		status = ST_EACCES;
	if (lstat(path, &stat) == 0)
	{
		if (S_ISLNK(stat.st_mode)
			&& (status == ST_ENOENT || follow_lnk != 0))
			return (follow_lnk != 0 ? ST_ISLNK : ST_ELOOP);
		if (!S_ISLNK(stat.st_mode) && status != ST_OK)
		{
			if (!S_ISDIR(stat.st_mode))
				return (ST_ENOTDIR);
			else if (status == ST_EACCES && t[i + 1] != NULL)
				return (ST_OK);
		}
	}
	return (status);
}

static int			do_not_follow_links(char **path, char **path_orig, char ***t,
						int i)
{
	char			buf[PATH_MAX];
	ssize_t			s;

	if ((s = readlink(*path, buf, PATH_MAX)) == -1)
		return (ST_READLINK);
	buf[s] = '\0';
	ft_memdel((void **)&(*path_orig));
	if (buf[0] == '/')
		*path_orig = ft_strdup(buf);
	else
		*path_orig = ft_strjoin3(*path, "/../", buf);
	if (*path_orig == NULL)
		return (ST_MALLOC);
	if ((*path_orig = builtin_cd_remove_dotdot(*path_orig)) == NULL)
		return (ST_MALLOC);
	ft_memdel((void **)&(*path));
	i++;
	while ((*t)[i])
	{
		*path = *path_orig;
		if ((*path_orig = ft_strjoin3(*path, "/", (*t)[i])) == NULL)
			return (ST_MALLOC);
		ft_memdel((void **)&(*path));
		i++;
	}
	ft_memdel_tab((void ***)&(*t));
	return (builtin_cd_chk_path(path_orig, 1));
}

int			builtin_cd_chk_path(char **path_orig, int follow_lnk)
{
	char				*path;
	char				**t;
	int					i;
	int					status;

	if (!(t = ft_strsplit(*path_orig, '/')))
		exit(ST_MALLOC);
	if (!(path = ft_strnew(ft_strlen(*path_orig))))
		exit(ST_MALLOC);
	if (*path_orig[0] == '/')
	{
		path[0] = '/';
		path[1] = '\0';
	}
	else
		path[0] = '\0';
	status = ST_OK;
	i = -1;
	while (status == ST_OK && t[++i] != NULL)
		status = builtin_cd_checkpath_element(path, t, i, follow_lnk);
	if (status == ST_ISLNK)
		return (do_not_follow_links(&path, path_orig, &t, i));
	ft_memdel((void **)&path);
	ft_memdel_tab((void ***)&t);
	log_debug("leaving builtin_cd_chk_path");
	return (status);
}

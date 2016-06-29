/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_chk_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "builtin_cd.h"

static int			s_builtin_cd_checkpath_element(char *path, char **t,
						int i, int follow_lnk)
{
	t_stat			stat;
	int				status;

	errno = 0;
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
		if (S_ISLNK(stat.st_mode) && (status == ST_ENOENT || follow_lnk != 0))
			return (errno == ELOOP ? ST_ELOOP : ST_ISLNK);
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

static int			s_do_not_follow_links(char **path, char **path_orig,
						char ***t, int i)
{
	int				ret;

	if ((ret = builtin_cd_readlink(*path, path_orig)) != ST_OK)
		return (ret);
	if ((*path_orig = builtin_cd_rm_dotdot(*path_orig)) == NULL)
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

int					builtin_cd_chk_path(char **path_orig, int follow_lnk)
{
	char			*path;
	char			**t;
	int				i;
	int				status;

	if (!(t = ft_strsplit(*path_orig, '/')))
		return (ST_MALLOC);
	if (!(path = ft_strnew(ft_strlen(*path_orig))))
		return (ST_MALLOC);
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
		status = s_builtin_cd_checkpath_element(path, t, i, follow_lnk);
	if (status == ST_ISLNK)
		return (s_do_not_follow_links(&path, path_orig, &t, i));
	ft_memdel((void **)&path);
	ft_memdel_tab((void ***)&t);
	return (status);
}

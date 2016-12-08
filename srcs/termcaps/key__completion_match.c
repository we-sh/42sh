#include "shell.h"
#include <dirent.h>

int		get_matchs(char *path, char *lookfor, t_list *matchs, size_t *ref_size)
{
	DIR				*dp;
	struct dirent	*ep;
	t_node_dir		*new;
	size_t			size;

	size = lookfor == NULL ? 0 : ft_strlen(lookfor);
	ASSERT(dp = opendir(path));
	while ((ep = readdir(dp)))
	{
		if (!ft_strcmp(ep->d_name, ".") || !ft_strcmp(ep->d_name, "..") ||
			(lookfor == NULL && ep->d_name[0] == '.') ||
			ft_memcmp(lookfor, ep->d_name, size))
			continue ;
		new = node_dir__create(ep);
		if (new == NULL)
			break ;
		list_push_back(&new->list, matchs);
		if (new->filename_size > *ref_size)
			*ref_size = new->filename_size;
	}
	closedir(dp);
	return (new == NULL ? 0 : 1);
}

int		match_binaries(char **envp, char *lookfor,
						t_list *matchs, size_t *ref_size)
{
	char	*env_path;
	char	**paths;
	size_t	i;

	if (lookfor == NULL)
		return (0);
	env_path = env_get_path(envp);
	ASSERT(env_path != NULL);
	paths = ft_strsplit(env_path, ':');
	ASSERT(paths != NULL);
	i = 0;
	while (paths[i])
	{
		if (!get_matchs(paths[i], lookfor, matchs, ref_size))
			return (0);
		free(paths[i]);
		i++;
	}
	free(paths);
	return (1);
}

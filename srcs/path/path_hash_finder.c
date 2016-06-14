#include "shell.h"

static int	s_get_new_cmd(char **commande, char *name, char *path)
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

static int	s_path_cmd_match_folder(char **cmd, char *dirname)
{
	char	*tmpcmd;

	tmpcmd = NULL;
	if (s_get_new_cmd(&tmpcmd, *cmd, dirname) == ST_OK)
	{
		if (access(tmpcmd, X_OK) != -1)
		{
			path_add_folder_content_to_hasht(*cmd, dirname);
			if (*cmd)
				free(*cmd);
			if ((*cmd = ft_strdup(tmpcmd)) == NULL)
				return (ST_MALLOC);
			if (tmpcmd)
				free(tmpcmd);
			tmpcmd = NULL;
			return (ST_OK);
		}
		if (tmpcmd)
			free(tmpcmd);
		tmpcmd = NULL;
	}
	return (ST_PATH_NOT_FOUND);
}

static int	s_path_commande_not_found_in_hasht(t_sh *sh, char **cmd)
{
	char	**folders;
	int		i;
	int		ret;

	i = 0;
	folders = ft_strsplit(env_get_path(sh->envp), ':');
	while (folders[i] != NULL)
	{
		if ((ret = s_path_cmd_match_folder(cmd, folders[i])) == ST_OK)
			return (ST_OK);
		else if (ret == ST_MALLOC)
			return (ST_MALLOC);
		i++;
	}
	ft_memdel_tab((void ***)&folders);
	return (ST_PATH_NOT_FOUND);
}

static int	s_path_iter_in_list(t_hasht *ptr, char **cmd)
{
	while (ptr->next)
	{
		if (ft_strcmp(*cmd, ptr->name) == 0)
		{
			if (s_get_new_cmd(cmd, ptr->name, ptr->path) != ST_OK)
				return (ST_MALLOC);
			return (ST_OK);
		}
		ptr = ptr->next;
	}
	return (ST_PATH_NOT_FOUND);
}

int			path_hash_finder(t_sh *sh, char **cmd)
{
	int		index;
	int		ret;

	if (*cmd == NULL)
		return (ST_OK);
	ret = ST_PATH_NOT_FOUND;
	index = fnv_64a_str(*cmd) % HASH_TABLE_SIZE;
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		if ((ft_strcmp(bodies[index].head->name, *cmd) != 0))
			ret = ST_PATH_NOT_FOUND;
		else if (s_get_new_cmd(cmd, bodies[index].head->name,
			bodies[index].head->path) == ST_MALLOC)
			return (ST_MALLOC);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		if ((ret = s_path_iter_in_list(bodies[index].head, cmd)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	log_info("%s",*cmd);
	if (ret == ST_PATH_NOT_FOUND &&
		ft_strncmp(*cmd, "/", 1) != 0 && ft_strncmp(*cmd, ".", 1) != 0)
	{
		if (s_path_commande_not_found_in_hasht(sh, cmd) == ST_PATH_NOT_FOUND)
		{
			ft_putstr_fd(*cmd, sh->fd);
			ft_putendl_fd(" : Command not found", sh->fd);
			return (ST_OK);
		}
	}
	if (access(*cmd, F_OK) == -1)
	{
		ft_putstr_fd(*cmd, sh->fd);
		ft_putendl_fd(" : Command not found", sh->fd);
		return (ST_OK);		
	}
	if (access(*cmd, X_OK) == -1)
	{
		ft_putstr_fd(*cmd, sh->fd);
		ft_putendl_fd(" : Permission denied", sh->fd);
	}
	return (ST_OK);
}

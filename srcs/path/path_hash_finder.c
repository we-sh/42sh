#include "shell.h"

static int		s_path_return_file_type(char *path)
{
	struct stat *st;
	int			ret;
	int			value;

	if ((st = (struct stat *)malloc(sizeof(struct stat))) == NULL)
		return (ST_MALLOC);
	if ((value = lstat(path, st)) == -1)
	{
		free(st);
		return (ST_CMD_NOT_FOUND);
	}
	if (S_ISREG(st->st_mode) && st->st_mode & 0111)
		ret = ST_OK;
	else if (S_ISDIR(st->st_mode))
		ret = ST_EISDIR;
	else
		ret = ST_CMD_NOT_FOUND;
	free(st);
	return (ret);
}

static int		s_path_iter_in_list(t_hasht *ptr, char **cmd)
{
	while (ptr)
	{
		if (ft_strcmp(*cmd, ptr->name) == 0)
		{
			if (path_get_new_cmd(cmd, ptr->name, ptr->path) == ST_MALLOC)
				return (ST_MALLOC);
			return (ST_OK);
		}
		ptr = ptr->next;
	}
	return (ST_CMD_NOT_FOUND);
}

static int		path_look_inside_hast(char **cmd, int index, int *ret)
{
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		*ret = ST_OK;
		if ((ft_strcmp(bodies[index].head->name, *cmd) != 0))
			*ret = ST_CMD_NOT_FOUND;
		else if (path_get_new_cmd(cmd, bodies[index].head->name,
			bodies[index].head->path) == ST_MALLOC)
			return (ST_MALLOC);
		if (*ret == ST_OK && access(*cmd, X_OK) == -1)
			return (ST_EACCES);
		return (ST_OK);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		*ret = ST_OK;
		if ((*ret = s_path_iter_in_list(bodies[index].head, cmd)) == ST_MALLOC)
			*ret = ST_MALLOC;
		if (*ret == ST_CMD_NOT_FOUND)
			return (ST_CMD_NOT_FOUND);
		if (*ret == ST_OK && access(*cmd, X_OK) == -1)
			return (ST_EACCES);
		return (ST_OK);
	}
	return (*ret);
}

static int		s_path_full(int *ret, char **cmd)
{
	if (*ret != ST_OK && access(*cmd, F_OK) != -1)
	{
		if ((*ret = s_path_return_file_type(*cmd)) != ST_OK)
		{
			if (*ret == ST_EISDIR)
				return (*ret);
			else if (access(*cmd, X_OK) == -1)
				return (ST_EACCES);
			else
				return (ST_CMD_NOT_FOUND);
		}
		return (*ret);
	}
	return (ST_OK);
}

int				path_hash_finder(char **envp, char **cmd)
{
	int			index;
	int			ret;

	if (*cmd == NULL)
		return (ST_OK);
	ret = ST_CMD_NOT_FOUND;
	index = fnv_a_str(*cmd) % HASH_TABLE_SIZE;
	if (ft_strncmp(*cmd, "./", 2) != 0 && 
		(ret = path_look_inside_hast(cmd, index, &ret)) != ST_CMD_NOT_FOUND)
		return (ret);
	if (ft_strncmp(*cmd, "/", 1) != 0 && ft_strncmp(*cmd, ".", 1) != 0)
	{
		if ((ret = path_commande_not_found_in_hasht(envp, cmd)) != ST_OK)
			return (ret);
	}
	if (ret != ST_OK && access(*cmd, X_OK) == -1)
		return (ST_EACCES);
	if ((ft_strncmp(*cmd, "/", 1) == 0 || ft_strncmp(*cmd, ".", 1) == 0))
		return (s_path_full(&ret, cmd));
	return (ST_OK);
}

#include "shell.h"

static int	s_path_iter_in_list(t_hasht *ptr, char **cmd)
{
	while (ptr->next)
	{
		if (ft_strcmp(*cmd, ptr->name) == 0)
		{
			if (path_get_new_cmd(cmd, ptr->name, ptr->path) != ST_OK)
				return (ST_MALLOC);
			return (ST_OK);
		}
		ptr = ptr->next;
	}
	return (ST_CMD_NOT_FOUND);
}

static	int	s_path_control_access(char **cmd, char **envp, int ret)
{
	if (ret == ST_CMD_NOT_FOUND &&
		ft_strncmp(*cmd, "/", 1) != 0 && ft_strncmp(*cmd, ".", 1) != 0)
	{
		if ((ret = path_commande_not_found_in_hasht(envp, cmd)) == ST_OK)
			return (ST_OK);
	}
	if (access(*cmd, F_OK) == -1)
	{
		display_status(ST_CMD_NOT_FOUND, *cmd, NULL);
		return (ST_OK);
	}
	if (access(*cmd, X_OK) == -1)
	{
		display_status(ST_EACCES, *cmd, NULL);
		return (ST_OK);
	}
	return (ret);
}

int			path_hash_finder(char **envp, char **cmd)
{
	int		index;
	int		ret;

	if (*cmd == NULL)
		return (ST_OK);
	ret = ST_CMD_NOT_FOUND;
	index = fnv_64a_str(*cmd) % HASH_TABLE_SIZE;
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		if ((ft_strcmp(bodies[index].head->name, *cmd) != 0))
			ret = ST_CMD_NOT_FOUND;
		else if (path_get_new_cmd(cmd, bodies[index].head->name,
			bodies[index].head->path) == ST_MALLOC)
			return (ST_MALLOC);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		if ((ret = s_path_iter_in_list(bodies[index].head, cmd)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	s_path_control_access(cmd, envp, ret);
	return (ST_OK);
}

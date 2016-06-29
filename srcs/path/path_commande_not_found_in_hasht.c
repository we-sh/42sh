#include "shell.h"

static int	s_path_cmd_match_folder(char **cmd, char *dirname)
{
	char	*tmpcmd;

	tmpcmd = NULL;
	if (path_get_new_cmd(&tmpcmd, *cmd, dirname) == ST_OK)
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
	return (ST_CMD_NOT_FOUND);
}

int			path_commande_not_found_in_hasht(char **envp, char **cmd)
{
	char	**folders;
	int		i;
	int		ret;

	i = 0;
	folders = ft_strsplit(env_get_path(envp), ':');
	while (folders[i] != NULL)
	{
		if ((ret = s_path_cmd_match_folder(cmd, folders[i])) == ST_OK)
			return (ST_OK);
		else if (ret == ST_MALLOC)
			return (ST_MALLOC);
		i++;
	}
	ft_memdel_tab((void ***)&folders);
	return (ST_CMD_NOT_FOUND);
}

#include "shell.h"

static int		s_path_cmd_match_folder(char **cmd,
										char *dirname,
										t_display_h *display,
										char **envp)
{
	char		*tmpcmd;

	tmpcmd = NULL;
	if (path_get_new_cmd(&tmpcmd, *cmd, dirname) == ST_OK)
	{
		if (access(tmpcmd, X_OK) != -1)
		{
			path_add_folder_content_to_hasht(*cmd, dirname, display, envp);
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

int				path_commande_not_found_in_hasht(char **envp, char **cmd)
{
	char		**folders;
	int			ret;
	char		*value;
	t_display_h	display;

	path_set_struct_display(&display);
	if ((value = env_get(envp, "PATH")) == NULL)
		return (ST_CMD_NOT_FOUND);
	if ((folders = ft_strsplit(value, ':')) == NULL)
		return (ST_MALLOC);
	while (folders[display.i] != NULL)
	{
		if ((ret = s_path_cmd_match_folder(cmd,
											folders[display.i],
											&display,
											envp))
												== ST_OK)
			return (ST_OK);
		else if (ret == ST_MALLOC)
			return (ST_MALLOC);
		display.i++;
	}
	ft_memdel_tab((void ***)&folders);
	return (ST_CMD_NOT_FOUND);
}

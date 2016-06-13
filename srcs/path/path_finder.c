# include "shell.h"

static char			*path_fill(DIR *directory, char *cmd, char *tab_path)
{
	t_dirent	content;
	char		*tmp;
	char		*value;

	value = NULL;
	while ((content = readdir(directory)) != NULL)
	{
		if (cmd && ft_strcmp(content->d_name, cmd) == 0)
		{
			tmp = ft_strjoin("/", content->d_name);
			value = ft_strjoin(tab_path, tmp);
			free(tmp);
			closedir(directory);
			return (value);
		}
	}
	return (value);
}

static char		*path_fill_folder_into_array(char *env_path, char *commande)
{
	DIR			*directory;
	char		*value;
	char		**folders;
	int			i;

	folders = ft_strsplit(env_path, ':');
	i = 0;
	value = NULL;
	while (folders[i] != NULL)
	{
		if ((directory = opendir(folders[i])) != NULL)
		{
			if ((value = path_fill(directory, commande, folders[i])) != NULL)
			{
				ft_memdel_tab((void ***)&folders);
				return (value);
			}
			closedir(directory);
		}
		i++;
	}
	ft_memdel_tab((void ***)&folders);
	return (NULL);
}

char		*path_finder(t_sh *sh, char *commande)
{
	char	*absolute_path;

	absolute_path = path_fill_folder_into_array(env_get_path(sh->envp), commande);
	return (absolute_path);
}

#include "shell.h"

int						path_init_hasht(char **envp)
{
	DIR					*directory;
	t_dirent			content;
	char				**folders;
	char				*value;
	int					i;

	i = 0;
	value = NULL;
	folders = ft_strsplit(env_get_path(envp), ':');
	while (folders[i] != NULL)
	{
		if ((directory = opendir(folders[i])) != NULL)
		{
			while (((content = readdir(directory)) != NULL))
			{
				if ((path_add_folder_content_to_hasht(content->d_name,
					folders[i])) == ST_MALLOC)
					return (ST_MALLOC);
			}
			closedir(directory);
		}
		i++;
	}
	ft_memdel_tab((void ***)&folders);
	return (ST_OK);
}

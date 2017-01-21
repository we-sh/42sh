#include "shell.h"
#include "libftprintf.h"
#include <dirent.h>

static void				s_path_display_result(t_display_h *display)
{
	ft_printf("Max collision:%d\n", display->max);
	ft_printf("Total total_binaries:%d\n", display->total_binaries);
	ft_printf("Total total folders:%d\n", display->folders_nbr--);
}

static int				s_path_opendir(char **folders,
										t_display_h *display,
										char **envp)
{
	DIR					*directory;
	t_dirent			content;

	if ((directory = opendir(folders[display->i])) != NULL)
	{
		if (env_get(envp, "HASH_TABLE"))
			ft_printf("Folders name:%s\n", folders[display->i]);
		while (((content = readdir(directory)) != NULL))
		{
			if ((path_add_folder_content_to_hasht(content->d_name,
				folders[display->i], display, envp)) == ST_MALLOC)
				return (ST_MALLOC);
		}
		display->folders_nbr++;
		closedir(directory);
	}
	return (ST_OK);
}

int						path_init_hasht(char **envp)
{
	char				**folders;
	char				*value;
	t_display_h			display;

	path_set_struct_display(&display);
	value = env_get(envp, "PATH");
	if (env_get(envp, "HASH_TABLE"))
		ft_putendl("Create a new hash table");
	folders = ft_strsplit(!value || value[0] == '\0' ? "." : value, ':');
	while (folders[display.i] != NULL && ft_strcmp(folders[display.i], ".")
		!= 0)
	{
		if ((s_path_opendir(folders, &display, envp)) != ST_OK)
			return (ST_MALLOC);
		display.i++;
	}
	if (env_get(envp, "HASH_TABLE"))
		s_path_display_result(&display);
	ft_memdel_tab((void ***)&folders);
	return (ST_OK);
}

#include "shell.h"

int						path_init_hasht(t_sh *sh)
{
	DIR					*directory;
	Fnv64_t 			hval;
	t_dirent			content;
	char				**folders;
	char				*value;
	int					i;

/*
*	debug
*/
	int					total;
	int 				collision;
	int					collisionmax;

	total = 0;
	collision = 0;
	collisionmax = 0;
/*
*	debug
*/ 
	hval = FNV1A_64_INIT;
	i = 0;
	value = NULL;
	folders = ft_strsplit(env_get_path(sh->envp), ':');
	while (folders[i] != NULL)
	{
		if ((directory = opendir(folders[i])) != NULL)
		{
			while (((content = readdir(directory)) != NULL))
			{
				if ((path_add_folder_content_to_hasht(&hval,
													content->d_name,
													folders[i],
													&collisionmax, 
													&collision)) == ST_MALLOC)
					return (ST_MALLOC);
				total++;
				log_info("Actual nbr of collision %s, %d", folders[i], collision);
			}	
		}
		closedir(directory);
		i++;
	}
	log_info("collisionmax :  %d", collisionmax);
	log_info("Nbr total de bianry  %d", total);
	return (ST_OK);
}

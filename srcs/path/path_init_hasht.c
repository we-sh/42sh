#include "shell.h"

static int 	s_add_new_node(t_dirent content, char *dirname, int *collisionmax, int *collision, int index)
{
	t_hasht				*ptr;
	t_hasht				*newm;
	int					tmpcol;//debug

	tmpcol = 0;//debug
	ptr = bodies[index].head;

	if ((newm = (t_hasht *)malloc(sizeof(t_hasht))) == NULL)
		return (ST_MALLOC);
	while (ptr->next)
	{
		tmpcol++;//debug
		ptr = ptr->next;
	}
	if (tmpcol > *collisionmax)//debug
		*collisionmax = tmpcol;//debug
	ptr->next = newm;
	if ((newm->path = ft_strdup(dirname)) == NULL)
		return (ST_MALLOC);
	if ((newm->name = ft_strdup(content->d_name)) == NULL)
		return (ST_MALLOC);
	newm->next = NULL;
	*collision = *collision + 1;//debug
	return (ST_OK);
}

static int				s_path_add_folder_content_to_hast(Fnv64_t *hval, t_dirent content, char *dirname, int *collisionmax, int *collision)
{
	unsigned long 		index;
	int 				nbr;

	nbr = 0;
	if (ft_strcmp(content->d_name, "..") != 0 &&
		content->d_name[0] != '.')
	{
		/*
		*
		*		Better dispersion
		*
		*		*hval = fnv_64a_str(content->d_name, *hval);
		*		index = (*hval%FNV_64_PRIME)%HASH_TABLE_SIZE;
		*
		*/
		
		index = fnv_64a_str(content->d_name, *hval);
		index = (index%FNV_64_PRIME)%HASH_TABLE_SIZE;
		log_info("Hval value = %lu", *hval);
		log_info("index = %d", index);
		log_info("name = %s", content->d_name);
		if (!bodies[index].head)
		{
			log_info("Empty");
			if ((bodies[index].head = (t_hasht *)malloc(sizeof(t_hasht))) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->path = ft_strdup(dirname)) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->name = ft_strdup(content->d_name)) == NULL)
				return (ST_MALLOC);
			bodies[index].head->next = NULL;
		}
		else
		{
			log_warn("Collision");
			if (s_add_new_node(content, dirname, collisionmax, collision, index) == ST_MALLOC)
				return (ST_MALLOC);
		}
	}
	return (ST_OK);
}

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
				if ((s_path_add_folder_content_to_hast(&hval,
													content,
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

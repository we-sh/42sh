#include "shell.h"
#include "fnv.h"

/*
*   Struct related to path_init_hasht.c
*/

#define HASH_TABLE_SIZE 5000


typedef struct          s_hasht{
    char                *path;
    char                *name;
    struct s_hasht      *next;
}                       t_hasht;



struct body
{
    t_hasht             *head;
};

struct body bodies[HASH_TABLE_SIZE];

/*
*   Struct related to path_init_hasht.c
*/

static int 	s_add_new_node(t_dirent content, char *dirname, int *collisionmax, int *collision, int index)
{
	t_hasht				*ptr;
	t_hasht				*newm;
	int					tmpcol;

	tmpcol = 0;//debug
	ptr = bodies[index].head;
	newm = (t_hasht *)malloc(sizeof(t_hasht));
	while (ptr->next)
	{
		tmpcol++;//debug
		ptr = ptr->next;
	}
	if (tmpcol > *collisionmax)//debug
		*collisionmax = tmpcol;
	ptr->next = newm;
	newm->path = ft_strdup(dirname);
	newm->name = ft_strdup(content->d_name);
	newm->next = NULL;
	*collision = *collision + 1;
	return (0);
}

static int				s_path_add_folder_content_to_hast(Fnv64_t *hval, t_dirent content, char *dirname, int *collisionmax, int *collision)
{
	unsigned long 		index;
	int 				nbr;

	nbr = 0;
	if (ft_strcmp(content->d_name, "..") != 0 &&
		content->d_name[0] != '.')
	{				
		*hval = fnv_64a_str(content->d_name, *hval);
		index = (*hval%FNV_64_PRIME)%HASH_TABLE_SIZE;
		log_info("index = %d", index);
		log_info("name = %s", content->d_name);
		if (!bodies[index].head)
		{
			log_info("Empty");
			bodies[index].head = (t_hasht *)malloc(sizeof(t_hasht));
			bodies[index].head->path = ft_strdup(dirname);
			bodies[index].head->name = ft_strdup(content->d_name);
			bodies[index].head->next = NULL;
		}
		else
		{
			log_warn("Collision");
			s_add_new_node(content, dirname, collisionmax, collision, index);
		}
	}
	return (0);
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
				s_path_add_folder_content_to_hast(&hval, content, folders[i], &collisionmax, &collision);
				total++;
				log_info("Nbr of collision for the folder %s, %d", folders[i], collision);
			}	
				
		}
		closedir(directory);
		i++;
	}

	log_info("collisionmax :  %d", collisionmax);
	log_info("Nbr total de bianry  %d", total);
	return (0);
}

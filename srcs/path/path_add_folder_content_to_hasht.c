#include "shell.h"

static int 	s_add_new_node(char *name, char *dirname, int *collisionmax, int *collision, int index)
{
	t_hasht				*ptr;
	t_hasht				*newm;
	int					tmpcol;//debug

	tmpcol = 0;//debug
	ptr = bodies[index].head;
	
	log_info("ADD NEW NODE");
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
	if ((newm->name = ft_strdup(name)) == NULL)
		return (ST_MALLOC);
	newm->next = NULL;
	*collision = *collision + 1;//debug
	log_info("ADD NEW NODE OK");

	return (ST_OK);
}

int				path_add_folder_content_to_hasht(Fnv64_t *hval, char *name, char *dirname, int *collisionmax, int *collision)
{
	unsigned long 		index;
	int 				nbr;

	nbr = 0;
	if (ft_strcmp(name, "..") != 0 &&
		name[0] != '.')
	{
		/*
		*
		*		Better dispersion
		*
		*		*hval = fnv_64a_str(content->d_name, *hval);
		*		index = (*hval%FNV_64_PRIME)%HASH_TABLE_SIZE;
		*
		*/
		index = fnv_64a_str(name, *hval);
		index = (index%FNV_64_PRIME)%HASH_TABLE_SIZE;
		log_info("Hval value = %lu", *hval);
		log_info("index = %d", index);
		log_info("name = %s", name);
		log_info("dirname = %s", dirname);
		if (!bodies[index].head)
		{
			log_info("Empty");
			if ((bodies[index].head = (t_hasht *)malloc(sizeof(t_hasht))) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->path = ft_strdup(dirname)) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->name = ft_strdup(name)) == NULL)
				return (ST_MALLOC);
			bodies[index].head->next = NULL;
		}
		else
		{
			log_info("Collision");
			if (s_add_new_node(name, dirname, collisionmax, collision, index) == ST_MALLOC)
			{
				log_warn("error s_add_new_node");
				return (ST_MALLOC);
			}
		}
	}
	return (ST_OK);
}
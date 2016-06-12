#include "shell.h"


static int s_get_new_cmd(char *commande, char *name, char *path)
{
	char				*tmp;
	char				*tmp2;

	if ((tmp = ft_strjoin("/",name)) == NULL)
		return (ST_MALLOC);
	if ((tmp2 = ft_strjoin(path, tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	free(commande);
	if((commande = ft_strdup(tmp2)) == NULL)
		return (ST_MALLOC);
	free(tmp2);
	return (ST_OK);
}

int 					path_hash_finder(t_sh *sh, char *commande)
{
	Fnv64_t				hval;
	int					index;
	t_hasht				*ptr;


	hval = fnv_64a_str(commande, FNV1A_64_INIT);
	//hval = hval * FNV_64_PRIME;
	index = (hval%FNV_64_PRIME)%HASH_TABLE_SIZE;
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		if (s_get_new_cmd(commande,
							bodies[index].head->name,
							bodies[index].head->path)
							!= ST_OK)
			return (ST_MALLOC);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		ptr = bodies[index].head;
		while (ptr->next)
		{
			if (ft_strcmp(commande, ptr->name) == 0 )
			{
				if (s_get_new_cmd(commande, ptr->name, ptr->path) != ST_OK)
					return (ST_MALLOC);
				return (ST_OK);
			}
			ptr = ptr->next;
		}
	}
	else
	{
		ft_putstr_fd(commande, sh->fd);
		ft_putendl_fd(" : Command not found", sh->fd);
		return (-1); /*USE ST COMMANDE NOT FOUND*/
	}
	return (ST_OK);
}
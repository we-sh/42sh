#include "shell.h"


static int s_get_new_cmd(char **commande, char *name, char *path)
{
	char				*tmp;
	char				*tmp2;

	if ((tmp = ft_strjoin("/",name)) == NULL)
		return (ST_MALLOC);
	if ((tmp2 = ft_strjoin(path, tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	free(*commande);
	if((*commande = ft_strdup(tmp2)) == NULL)
		return (ST_MALLOC);
	free(tmp2);
	return (ST_OK);
}

int 					path_hash_finder(t_sh *sh, char **commande)
{
	Fnv64_t				hval;
	t_hasht				*ptr;
	char				**folders;
	char				*tmpcmd;
	int					index;
	int					i;

	i = 0;
	tmpcmd = NULL;
	hval = fnv_64a_str(*commande, FNV1A_64_INIT);
	index = (hval%FNV_64_PRIME)%HASH_TABLE_SIZE;
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		if (s_get_new_cmd(commande,
							bodies[index].head->name,
							bodies[index].head->path)
							!= ST_OK)
			return (ST_MALLOC);
		else
			return (ST_OK);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		ptr = bodies[index].head;
		while (ptr->next)
		{
			if (ft_strcmp(*commande, ptr->name) == 0 )
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
		folders = ft_strsplit(env_get_path(sh->envp), ':');
		while (folders[i] != NULL)
		{
			if (s_get_new_cmd(&tmpcmd, *commande, folders[i]) == ST_OK)
			{
				log_warn(" Commande test %s", tmpcmd);
				if (access(tmpcmd, X_OK) != -1)
				{
					log_warn(" : Command exist in the path but not in hash table");
					hval = FNV1A_64_INIT;
					path_add_folder_content_to_hasht(&hval, *commande, folders[i], &i, &i);
					if (*commande)
						free(*commande);
					*commande = ft_strdup(tmpcmd);
					log_warn("NEW COMMANDE %s", *commande);
					if (tmpcmd)
						free(tmpcmd);
					tmpcmd = NULL;
					return (ST_OK);
				}
				if (tmpcmd)
					free(tmpcmd);
				tmpcmd = NULL;
			}
			i++;
		}
		if (tmpcmd == NULL)
		{		
			log_warn("tmpcmd Value : %s", *commande);
			if (access(*commande, X_OK) != -1)
			{
				log_warn(" : Command exist with absolute : %s", *commande);
				return (ST_OK);
			}	
		}
			ft_putstr_fd(*commande, sh->fd);
			ft_putendl_fd(" : Command not found", sh->fd);
			return (-1); /*USE ST COMMANDE NOT FOUND*/
	}
	return (ST_OK);
}
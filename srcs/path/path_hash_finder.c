#include "shell.h"

static int				s_get_new_cmd(char **commande, char *name, char *path)
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

static int				s_path_check_if_cmd_match_with_folder(char **commande, char *dirname)
{
	Fnv64_t				hval;
	char				*tmpcmd;

	tmpcmd = NULL;
	hval = FNV1A_64_INIT;
	if (s_get_new_cmd(&tmpcmd, *commande, dirname) == ST_OK)
	{
		if (access(tmpcmd, X_OK) != -1)
		{
			hval = FNV1A_64_INIT;
			path_add_folder_content_to_hasht(&hval, *commande, dirname);
			if (*commande)
				free(*commande);
			*commande = ft_strdup(tmpcmd);
			if (tmpcmd)
				free(tmpcmd);
			tmpcmd = NULL;
			return (ST_OK);
		}
		if (tmpcmd)
			free(tmpcmd);
		tmpcmd = NULL;
	}
	return (-1); //add got return
}

static int				s_path_commande_not_found_in_hasht(t_sh *sh, char **commande)
{	
	char				**folders;
	char				*tmpcmd;
	int					i;

	i = 0;
	tmpcmd = NULL;
	folders = ft_strsplit(env_get_path(sh->envp), ':');
	while (folders[i] != NULL)
	{
		if (s_path_check_if_cmd_match_with_folder(commande, folders[i]) != ST_OK)
			tmpcmd = NULL;
		i++;
	}
	ft_memdel_tab((void ***)&folders);
	if (tmpcmd == NULL)
	{		
		if (access(*commande, X_OK) != -1)
			return (ST_OK);
	}
	return (ST_PATH_NOT_FOUND);
}

static int 				s_path_iter_in_list(t_hasht *ptr, char **commande)
{
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
	return (ST_PATH_NOT_FOUND);
}

int 					path_hash_finder(t_sh *sh, char **commande)
{
	int					index;

	index = ((fnv_64a_str(*commande, FNV1A_64_INIT))%FNV_64_PRIME)%HASH_TABLE_SIZE;
	if (bodies[index].head != NULL && !bodies[index].head->next)
	{
		if (s_get_new_cmd(commande, bodies[index].head->name, bodies[index].head->path)	!= ST_OK)
			return (ST_MALLOC);
		else
			return (ST_OK);
	}
	else if (bodies[index].head != NULL && bodies[index].head->next)
	{
		if (s_path_iter_in_list(bodies[index].head, commande) == ST_MALLOC)
			return (ST_MALLOC);
	}
	else
	{
		if (s_path_commande_not_found_in_hasht(sh, commande) == ST_PATH_NOT_FOUND)
		{
			ft_putstr_fd(*commande, sh->fd);
			ft_putendl_fd(" : Command not found", sh->fd);
			return (ST_OK);
		}
	}
	return (ST_OK);
}
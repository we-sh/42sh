#include "shell.h"
#include "libftprintf.h"

static int		s_add_new_node(char *name, char *dirname, int index, int *max)
{
	t_hasht		*ptr;
	t_hasht		*newm;
	int			cmpt;

	cmpt = 0;
	ptr = bodies[index].head;
	if ((newm = (t_hasht *)malloc(sizeof(t_hasht))) == NULL)
		return (ST_MALLOC);
	while (ptr->next)
	{
		cmpt++;
		if (cmpt > *max)
			*max = cmpt;
		ptr = ptr->next;
	}
	ptr->next = newm;
	if ((newm->path = ft_strdup(dirname)) == NULL)
		return (ST_MALLOC);
	if ((newm->name = ft_strdup(name)) == NULL)
		return (ST_MALLOC);
	newm->next = NULL;
	return (ST_OK);
}

static int		s_add_first_new_node(char *name, char *dirname, int index)
{
	if ((bodies[index].head = (t_hasht *)malloc(sizeof(t_hasht)))
			== NULL)
		return (ST_MALLOC);
	if ((bodies[index].head->path = ft_strdup(dirname)) == NULL)
		return (ST_MALLOC);
	if ((bodies[index].head->name = ft_strdup(name)) == NULL)
		return (ST_MALLOC);
	bodies[index].head->next = NULL;
	return (ST_OK);
}

int				path_add_folder_content_to_hasht(char *name,
													char *dirname,
													t_display_h *display,
													char **envp)
{
	int			nbr;
	int			index;

	nbr = 0;
	if (ft_strcmp(name, "..") != 0 && name[0] != '.')
	{
		if (env_get(envp, "HASH_TABLE"))
			ft_printf("\tBinary name:%s\n", name);
		index = fnv_a_str(name) % HASH_TABLE_SIZE;
		if (!bodies[index].head)
		{
			if ((s_add_first_new_node(name, dirname, index)) != ST_OK)
				return (ST_MALLOC);
			display->total_binaries += 1;
		}
		else
		{
			if (s_add_new_node(name, dirname, index, &display->max)
				== ST_MALLOC)
				return (ST_MALLOC);
			display->total_binaries += 1;
		}
	}
	return (ST_OK);
}

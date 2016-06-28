#include "shell.h"

static int		s_add_new_node(char *name, char *dirname, int index)
{
	t_hasht		*ptr;
	t_hasht		*newm;

	ptr = bodies[index].head;
	if ((newm = (t_hasht *)malloc(sizeof(t_hasht))) == NULL)
		return (ST_MALLOC);
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = newm;
	if ((newm->path = ft_strdup(dirname)) == NULL)
		return (ST_MALLOC);
	if ((newm->name = ft_strdup(name)) == NULL)
		return (ST_MALLOC);
	newm->next = NULL;
	return (ST_OK);
}

int				path_add_folder_content_to_hasht(char *name, char *dirname)
{
	int			nbr;
	int			index;
	static int zb= 0;

	nbr = 0;
	if (ft_strcmp(name, "..") != 0 && name[0] != '.')
	{
		index = fnv_a_str(name) % HASH_TABLE_SIZE;
		if (!bodies[index].head)
		{
			if ((bodies[index].head =
				(t_hasht *)malloc(sizeof(t_hasht))) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->path = ft_strdup(dirname)) == NULL)
				return (ST_MALLOC);
			if ((bodies[index].head->name = ft_strdup(name)) == NULL)
				return (ST_MALLOC);
			bodies[index].head->next = NULL;
		}
		else
		{
			if (s_add_new_node(name, dirname, index) == ST_MALLOC)
				return (ST_MALLOC);
			zb++;
		}
	}
	return (ST_OK);
}

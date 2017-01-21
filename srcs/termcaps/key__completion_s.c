#include "shell.h"
#include <dirent.h>

t_node_dir		*node_dir__create(const struct dirent *ep)
{
	t_node_dir	*new;
	size_t		filename_size;

	filename_size = ft_strlen(ep->d_name);
	new = malloc(sizeof(t_node_dir));
	if (!new)
		return (NULL);
	new->filename_size = filename_size;
	ft_memcpy(new->filename, ep->d_name, filename_size + 1);
	new->d_type = ep->d_type;
	return (new);
}

void			list_dir__destroy(t_list *head)
{
	t_list		*pos;
	t_list		*safe;
	t_node_dir	*node_dir;

	safe = head->next;
	while ((pos = safe) && (pos != head))
	{
		safe = safe->next;
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		free(node_dir);
	}
}

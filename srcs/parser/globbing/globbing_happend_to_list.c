#include "shell.h"

static int		s_happend_next(t_mylist **list, char *input)
{
	t_mylist	*newm;
	t_mylist	*ptr;

	if ((newm = (t_mylist*)ft_memalloc(sizeof(t_mylist))) == NULL)
		return (ST_MALLOC);
	ptr = *list;
	while (ptr->next)
	{
		if (ft_strcmp(ptr->content, input) == 0)
		{
			free(newm);
			return (ST_OK);
		}
		ptr = ptr->next;
	}
	ptr->next = newm;
	if ((newm->content = ft_strdup(input)) == NULL)
		return (ST_MALLOC);
	newm->next = NULL;
	return (ST_OK);
}

int				globbing_happend_to_list(t_mylist **list, char *input)
{
	if (*list == NULL)
	{
		if ((*list = (t_mylist*)ft_memalloc(sizeof(t_mylist))) == NULL)
			return (ST_MALLOC);
		if (((*list)->content = ft_strdup(input)) == NULL)
			return (ST_MALLOC);
		(*list)->next = NULL;
	}
	else
	{
		if ((s_happend_next(list, input)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

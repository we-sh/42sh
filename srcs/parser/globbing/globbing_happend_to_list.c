#include "shell.h"

int globbing_happend_to_list(t_mylist **list, char *input)
{
	t_mylist    *newm;
	t_mylist    *ptr;

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
	}
	return (ST_OK);
}

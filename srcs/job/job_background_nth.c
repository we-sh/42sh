#include "shell.h"

/*
** This function iterates on job list and return the nth
** background job, or NULL if none is found.
*/

static t_job	*s_reverse(t_list *tmp, int i, const t_list *head,
					const int index)
{
	t_job		*j;

	j = NULL;
	while (i > index)
	{
		tmp = tmp->prev;
		if (tmp == head)
			return (NULL);
		j = CONTAINER_OF(tmp, t_job, list_job);
		if (j->foreground == 0)
			i--;
	}
	return (j);
}

t_job			*job_background_nth(const t_list *head, const int index)
{
	t_job		*j;
	t_list		*tmp;
	int			i;

	j = NULL;
	tmp = (t_list *)head;
	i = 0;
	if (index > 0)
	{
		while (i < index)
		{
			tmp = tmp->next;
			if (tmp == head)
				return (NULL);
			j = CONTAINER_OF(tmp, t_job, list_job);
			if (j->foreground == 0)
				i++;
		}
		return (j);
	}
	return (s_reverse(tmp, i, head, index));
}

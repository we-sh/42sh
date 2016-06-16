#include "shell.h"

void			path_free_hasht(void)
{
	int			i;
	t_hasht		*tmp;

	i = 0;
	while (i < 5000)
	{
		tmp = NULL;
		while (bodies[i].head)
		{
			tmp = bodies[i].head->next;
			free(bodies[i].head->path);
			free(bodies[i].head->name);
			free(bodies[i].head);
			bodies[i].head = tmp;
		}
		i++;
	}
}

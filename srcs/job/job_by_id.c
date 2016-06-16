#include "shell.h"

t_job	*job_by_id(int const id, int const foreground)
{
	t_list	*j_pos;
	t_job	*j;

	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == foreground)
			if (j->id == id)
				return (j);
	}
	return (NULL);
}

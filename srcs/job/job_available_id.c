#include "shell.h"

int	job_available_id(void)
{
	int		id;
	int		exists;
	t_list	*j_pos;
	t_job	*j;

	id = 0;
	while (++id)
	{
		exists = 0;
		LIST_FOREACH(&g_current_jobs_list_head, j_pos)
		{
			j = CONTAINER_OF(j_pos, t_job, list_job);
			if (j->id == id)
			{
				exists = 1;
				break;
			}
		}
		if (exists == 0)
			break;
	}
	return (id);
}

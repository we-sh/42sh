#include "shell.h"

void	job_list_clean(int notified)
{
	t_job	*j;
	t_list	*pos;
	t_list	*safe;
	t_list	*head;

	head = &g_current_jobs_list_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		j = CONTAINER_OF(pos, t_job, list_job);
		if (notified == 0 || j->notified == 1)
		{
			log_debug("freeing job %i", j->pgid);
			pos->prev->next = safe;
			safe->prev = pos->prev;
			job_free(&j);
		}
	}
}

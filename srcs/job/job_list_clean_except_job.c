#include "shell.h"

void	job_list_clean_except_job(t_job *j)
{
	t_job	*j_cur;
	t_list	*pos;
	t_list	*safe;
	t_list	*head;

	head = &g_current_jobs_list_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		j_cur = CONTAINER_OF(pos, t_job, list_job);
		if (j->id != j_cur->id)
		{
			pos->prev->next = safe;
			safe->prev = pos->prev;
			job_free(&j_cur);
		}
	}
}

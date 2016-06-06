#include "shell.h"

void	job_set_stopped(t_job *j, int const stopped)
{
	t_list	*p_pos;
	t_proc	*p;

	LIST_FOREACH(&j->proc_head, p_pos)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
		p->stopped = stopped;
	}
}

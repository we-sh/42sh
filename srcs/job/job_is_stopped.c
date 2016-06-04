#include "shell.h"

/*
** This function returns 1 if the given job t_job is stopped.
** A job is stopped when all of its own processes are marked as stopped.
*/

int	job_is_stopped(t_job *j)
{
	t_list		*head;
	t_list		*pos;
	t_proc		*p;

	head = &j->proc_head;
	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		if (p->stopped == 0)
			return (0);
	}
	return (1);
}

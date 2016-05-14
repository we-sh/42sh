#include "shell.h"

/*
** This function returns 1 if the given job t_job is completed.
** A job is completed when all of its own processes are marked as completed.
*/

int	job_is_completed(t_job *j)
{
	t_proc		*p;

	p = j->proc;
	while (p)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

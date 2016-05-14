#include "shell.h"

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

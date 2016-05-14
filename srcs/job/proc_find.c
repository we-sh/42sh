#include "shell.h"

/*
** This function returns a process `t_proc` found through its PID.
** It iterates on the current job list.
** It returns NULL when no one is found.
*/

t_proc	*proc_find(pid_t pid)
{
	t_job	*j;
	t_proc	*p;

	j = g_current_jobs;
	while (j)
	{
		p = j->proc;
		while(p)
		{
			if (p->pid == pid)
				return (p);
			p = p->next;
		}
		j = j->next;
	}
	return (NULL);
}

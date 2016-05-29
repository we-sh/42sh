#include "shell.h"

/*
** This function returns a process `t_proc` found through its PID.
** It iterates on the current job list.
** It returns NULL when no one is found.
*/

t_proc	*proc_find(pid_t pid)
{
	t_list	*j_pos;
	t_job	*j;
	t_list	*p_pos;
	t_proc	*p;

	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		LIST_FOREACH(&j->proc_head, p_pos)
		{
			p = CONTAINER_OF(p_pos, t_proc, list_proc);
			if (p->pid == pid)
			{
				return (p);
			}
		}
	}
	return (NULL);
}

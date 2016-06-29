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

	j_pos = &g_current_jobs_list_head;
	while ((j_pos = j_pos->next) && j_pos != &g_current_jobs_list_head)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		p_pos = &j->proc_head;
		while ((p_pos = p_pos->next) && p_pos != &j->proc_head)
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

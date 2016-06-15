#include "shell.h"

/*
**
*/

int	job_wait(t_job *j_orig)
{
	int		status;
	pid_t			pid;
	t_list	*j_pos;
	t_job	*j;
	t_list	*p_pos;
	t_proc	*p;

	log_info("a");
	log_info("job list size : %zu", list_size(&g_current_jobs_list_head));
	log_info("b");
	while (1)
	{
		LIST_FOREACH(&g_current_jobs_list_head, j_pos)
		{
		//	log_debug("loop 2");
			j = CONTAINER_OF(j_pos, t_job, list_job);
			if (j->foreground == 1)
			{
				LIST_FOREACH(&j->proc_head, p_pos)
				{
		//	log_debug("loop 3");
					p = CONTAINER_OF(p_pos, t_proc, list_proc);
					if (p->completed == 0 && p->stopped == 0)
					{
						errno = 0;
						pid = waitpid(p->pid, &status, WUNTRACED);
						if (pid < 0 && errno == ECHILD)
						{
							p->completed = 1;
						}
						else
						{
							proc_update_status(pid, status);
						}
					}
				}
			}
		}
		if (job_is_completed(j_orig) == 1 || job_is_stopped(j_orig) == 1)
			break;
	}
	return (ST_OK);
}

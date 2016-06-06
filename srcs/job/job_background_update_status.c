#include "shell.h"

/*
**
*/

int	job_background_update_status(void)
{
	int		status;
	pid_t			pid;
	t_list	*j_pos;
	t_job	*j;
	t_list	*p_pos;
	t_proc	*p;

	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == 0)
		{
			log_debug("checking status of background job %d", j->pgid);
			LIST_FOREACH(&j->proc_head, p_pos)
			{
				p = CONTAINER_OF(p_pos, t_proc, list_proc);
				log_debug("proc info %d, completed: %d, stopped: %d, notified: %d", p->pid, p->completed, p->stopped, j->notified);
				if (p->completed == 0 && p->stopped == 0)
				{
					log_debug("checking status of background process %d", p->pid);
					errno = 0;
					pid = waitpid(p->pid, &status, WNOHANG | WUNTRACED);
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
			if (job_is_completed(j) == 1)
			{
				// todo notify user
				log_debug("background job is completed %d", j->pgid);
				j->notified = 1;
			}
		}
	}
	return (ST_OK);
}

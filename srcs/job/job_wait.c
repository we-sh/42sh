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

	while (1)
	{
		LIST_FOREACH(&g_current_jobs_list_head, j_pos)
		{
			j = CONTAINER_OF(j_pos, t_job, list_job);
			LIST_FOREACH(&j->proc_head, p_pos)
			{
				p = CONTAINER_OF(p_pos, t_proc, list_proc);
				errno = 0;
				pid = waitpid(p->pid, &status, WUNTRACED);
				if (errno == ECHILD)
					p->completed = 1;
				else
					proc_update_status(pid, status);
			}
		}
		if (job_is_completed(j_orig) == 1 || job_is_stopped(j_orig) == 1)
			break;
	}
	return (ST_OK);
}
/*
int	job_wait(t_job *j)
{
	int		status;
	pid_t			pid;

	log_debug("waiting for job to complete");
	while (1)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (proc_update_status(pid, status) == 0
			|| job_is_stopped(j) == 1
			|| job_is_completed(j) == 1)
			break ;
	}
	log_debug("job completed: %d, stopped: %d", job_is_completed(j), job_is_stopped(j));
	return (ST_OK);
}
*/

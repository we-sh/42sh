#include "shell.h"

/*
** This function check for the statuses of the background jobs
** and display a notification to the user if their status changed.
*/

static void	s_iterate_on_proc(t_job *j)
{
	int		status;
	pid_t	pid;
	t_list	*p_pos;
	t_proc	*p;

	LIST_FOREACH(&j->proc_head, p_pos)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
		if (p->completed == 0)
		{
			errno = 0;
			pid = waitpid(p->pid, &status, WCONTINUED | WNOHANG | WUNTRACED);
			if (pid < 0 && errno == ECHILD)
				p->completed = 1;
			else
				proc_update_status(j, pid, status);
		}
	}
}

static int	s_status_has_changed(t_job *j)
{
	int		old_completed;
	int		old_stopped;

	old_completed = job_is_completed(j);
	old_stopped = job_is_stopped(j);
	s_iterate_on_proc(j);
	if (old_completed != job_is_completed(j) == 1
		|| old_stopped != job_is_stopped(j) == 1)
		return (1);
	return (0);
}

int			job_background_update_status(void)
{
	t_list	*j_pos;
	t_job	*j;
	int		total;

	total = 0;
	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == 0)
		{
			if (s_status_has_changed(j) == 1)
			{
				total++;
				ft_putchar('\n');
				job_display_status(j, 1);
				if (job_is_completed(j) == 1)
					j->notified = 1;
			}
		}
	}
	if (total > 0)
		job_list_clean(1);
	return (total);
}

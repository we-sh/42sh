#include "shell.h"

/*
** This function waits for running jobs in foreground until they are
** marked as `stopped` or `completed`.
*/

static void	s_proc_status(t_job *j, t_proc *p)
{
	int		status;
	pid_t	pid;

	if (p->completed == 0 && p->stopped == 0)
	{
		errno = 0;
		pid = waitpid(p->pid, &status, WUNTRACED);
		if (pid < 0 && errno == ECHILD)
			p->completed = 1;
		else
			proc_update_status(j, pid, status);
	}
}

int	job_wait(t_job *j_orig)
{
	t_list	*j_pos;
	t_job	*j;
	t_list	*p_pos;

	while (1)
	{
		LIST_FOREACH(&g_current_jobs_list_head, j_pos)
		{
			j = CONTAINER_OF(j_pos, t_job, list_job);
			if (j->launched == 1 && j->foreground == 1)
				LIST_FOREACH(&j->proc_head, p_pos)
				{
					s_proc_status(j, CONTAINER_OF(p_pos, t_proc, list_proc));
				}
		}
		if (job_is_completed(j_orig) == 1 || job_is_stopped(j_orig) == 1)
			break;
	}
	if (job_is_signaled(j_orig))
	{
		ft_putchar('\n');
		job_display_status(j_orig, 1);
	}
	return (ST_OK);
}

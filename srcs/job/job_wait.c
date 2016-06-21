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

static void	s_notify(t_job *j)
{
	int		sig;

	sig = job_is_signaled(j);
	if (sig != 0 || (job_is_stopped(j) == 1 && job_is_completed(j) == 0))
	{
		if (sig != SIGINT && sig != SIGQUIT)
		{
			ft_putchar('\n');
			job_display_status(j, 1);
		}
	}
}

int			job_wait(t_job *j_orig)
{
	t_list	*j_pos;
	t_job	*j;
	t_list	*p_pos;

	while (1)
	{
		j_pos = &g_current_jobs_list_head;
		while ((j_pos = j_pos->next) && j_pos != &g_current_jobs_list_head)
		{
		//	log_debug("loop 2");
			j = CONTAINER_OF(j_pos, t_job, list_job);
			if (j->launched == 1 && j->foreground == 1)
			{
				p_pos = &j->proc_head;
				while ((p_pos = p_pos->next) && p_pos != &j->proc_head)
				{
					s_proc_status(j, CONTAINER_OF(p_pos, t_proc, list_proc));
				}
			}
		}
		if (job_is_completed(j_orig) == 1 || job_is_stopped(j_orig) == 1)
			break ;
	}
	s_notify(j_orig);
	return (ST_OK);
}

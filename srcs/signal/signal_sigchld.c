#include "shell.h"

static void	s_job_notification (void)
{
	t_job	*j;
	t_job	*j_next;

	j = g_current_jobs;
	while (j)
	{
		j_next = j->next;
		if (job_is_completed(j) == 1)
		{
			// check if it is a background job
			// and warn user about its status
			//if (is_job_stopped(j) == 1 || j->foreground == 0)
			//{
			//	display a message "job completed"
			//	reinit_prompt();
			//}

			// remove job from list of current jobs
			if (j->prev)
				j->prev->next = j->next;
			else
				g_current_jobs = j->next;
			if (j->next)
				j->next->prev = j->prev;

			// todo: free job
		}
		// else Ctrl + Z
		//else if (is_job_stopped(j) == 1 && j->notified == 0)
		//{
		//	format_job_info (j, "stopped");
		//	j->notified = 1;
		//}

		j = j_next;
	}
}

void	signal_sigchld(int sig)
{
	int		status;
	pid_t	pid;

	log_debug("SIGCHLD received\n");
	if (sig == SIGCHLD)
	{
		errno = 0;
		while (1)
		{
			pid = waitpid (WAIT_ANY, &status, WUNTRACED | WNOHANG);
			if (proc_update_status(pid, status) == 0)
				break ;
		}
		s_job_notification();
	}
}

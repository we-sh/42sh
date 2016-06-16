#include "shell.h"

/*
** This function saves the status of a process retrieved through
** the function `waitpid`.
*/

static void	s_set_flags(t_job *j, t_proc *p, int const status)
{
	p->exit_status = WEXITSTATUS(status);
	if (WIFSTOPPED(status))
	{
		p->stopped = 1;
		j->foreground = 0;
		j->notified = 0;
	}
	else
	{
		p->stopped = 0;
		if (WIFEXITED(status) || WIFSIGNALED(status))
		{
			p->completed = 1;
			if (WIFSIGNALED(status))
				p->signaled = WTERMSIG(status);
		}
	}
}

int			proc_update_status(t_job *j, pid_t pid, int status)
{
	t_proc		*p;

	if (pid == 0 || errno == ECHILD)
	{
		errno = 0;
		return (-1);
	}
	else if (pid < 0)
		return (-1);
	if ((p = proc_find(pid)) != NULL)
	{
		s_set_flags(j, p, status);
		log_debug("proc %d exited with %d status (stopped: %d, completed: %d)", pid, p->exit_status, p->stopped, p->completed);
		return (0);
	}
	return (-1);
}

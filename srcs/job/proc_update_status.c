#include "shell.h"

/*
** This function saves the status of a process retrieved through
** the function `waitpid`.
*/

int	proc_update_status(pid_t pid, int status)
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
		p->exit_status = WEXITSTATUS(status);
		log_debug("proc %d exited with %d", pid, p->exit_status);
		if (WIFSTOPPED(status))
			p->stopped = 1;
		else
		{
			p->completed = 1;
			if (WIFSIGNALED(status))
			{
				log_debug("proc %d signal recieved: %d", pid, WTERMSIG(status));
				// notify user about signal (segfault, sigabort...)
			}
		}
		log_debug("proc %d status: stopped %d, completed %d", pid, p->stopped, p->completed);
		return (0);
	}
	return (-1);
}

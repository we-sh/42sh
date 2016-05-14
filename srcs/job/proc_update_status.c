#include "shell.h"

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
		if (WIFSTOPPED(status))
			p->stopped = 1;
		else
		{
			p->completed = 1;
			if (WIFSIGNALED(status))
			{
				// notify user about signal (segfault, sigabort...)
			}
		}
		return (0);
	}
	return (-1);
}

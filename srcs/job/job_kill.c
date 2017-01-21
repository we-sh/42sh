#include "shell.h"
#include <sys/ioctl.h>
#include <signal.h>

int	job_kill(t_sh *sh, t_job *j, int status)
{
	if (j->pgid != 0)
	{
		kill(-j->pgid, SIGTERM);
		kill(-j->pgid, SIGCONT);
	}
	j->notified = 1;
	if (ioctl(sh->fd, TIOCSPGRP, &sh->pgid) == -1)
	{
		if (status != ST_OK)
			status = ST_TCSETPGRP;
	}
	return (status);
}

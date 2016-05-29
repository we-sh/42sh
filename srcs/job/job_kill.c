#include "shell.h"

int	job_kill(t_sh *sh, t_job *j, int status)
{
	if (j->pgid != 0)
	{
		kill(-j->pgid, SIGTERM);
		kill(-j->pgid, SIGCONT);
	}
	j->notified = 1;
	if (tcsetpgrp(sh->fd, sh->pgid) == -1)
	{
		if (status != ST_OK)
		 	status = ST_TCSETPGRP;
	}
	if (tcsetattr(sh->fd, TCSADRAIN, &sh->termios_new) == -1)
	{
		if (status != ST_OK)
			status = ST_TCSETATTR;
	}
	return (status);
}

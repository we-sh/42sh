#include "shell.h"

int	job_kill(t_job *j, int status)
{
	if (j->pgid != 0)
	{
		kill(-j->pgid, SIGTERM);
		kill(-j->pgid, SIGCONT);
	}
	return (status);
}

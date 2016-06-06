#include "shell.h"

int		job_background(t_job *j, int const sigcont)
{
	if (sigcont == 1)
		if (kill (-j->pgid, SIGCONT) < 0)
		{
			perror ("kill (SIGCONT)");
			// todo
		}
	job_set_stopped(j, 0);
	j->notified = 0;
	job_display_status(j, 1);
	return (ST_OK);
}

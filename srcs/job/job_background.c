#include "shell.h"

int		job_background(t_job *j, int const sigcont)
{
	if (sigcont == 1)
		if (kill (-j->pgid, SIGCONT) < 0)
		{
			perror ("kill (SIGCONT)");
			// todo
		}
	return (ST_OK);
}

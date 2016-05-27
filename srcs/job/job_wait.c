#include "shell.h"

/*
**
*/

int	job_wait(t_job *j)
{
	int		status;
	pid_t			pid;

	log_debug("waiting for job to complete");
	while (1)
	{
		errno = 0;
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (proc_update_status(pid, status) == 0
			|| job_is_stopped(j) == 1
			|| job_is_completed(j) == 1)
			break ;
	}
	log_debug("job completed: %d, stopped: %d", job_is_completed(j), job_is_stopped(j));
	return (ST_OK);
}

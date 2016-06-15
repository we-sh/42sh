#include "shell.h"

/*
** This function put a given job into foreground, may restart a stopped job
** by sending to it the signal SIGCONT and wait for it to complete or
** stop.
** It waits for the job to report its status and then put the Shell
** back to foreground, letting the user enter a new command.
*/

static int	s_bask_to_shell(t_sh *sh)
{
	int	ret;

	ret = ST_OK;
	if (tcsetpgrp(sh->fd, sh->pgid) == -1)
	{
		log_fatal("s_bask_to_shell: tcsetpgrp failed");
		ret = ST_TCSETPGRP;
	}
	return (ST_OK);
}

int			job_foreground(t_sh *sh, t_job *j, int const sigcont)
{
	log_debug("put job to foreground (id: %d, pgid: %d)", j->id, j->pgid);
	job_set_stopped(j, 0);
	j->notified = 1;
	j->foreground = 1;
	if (sigcont == 1)
	{
		log_debug("sending SIGCONT to job %i", j->pgid);
		if (kill(-j->pgid, SIGCONT) < 0)
		{
			log_error("failed to continue the stopped job %d", j->pgid);
			return (job_kill(sh, j, ST_SIGCONT));
		}
	}
	if (tcsetpgrp(sh->fd, j->pgid) == -1 && errno != EINVAL)
	{
		log_error("failed to make the job %d to control terminal", j->pgid);
		return (job_kill(sh, j, ST_TCSETPGRP));
	}
	job_wait(j);
	if (job_is_completed(j) == 0 && tcgetattr(sh->fd, &j->tmodes) != 0)
	{
		// todo notify user a problem occured
		log_error("failed to save termios structure a the job %d", j->pgid);
	}
	return (s_bask_to_shell(sh));
}

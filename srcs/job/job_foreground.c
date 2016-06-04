#include "shell.h"

/*
** This function put a given job into foreground, may restart a stopped job
** by sending to it the signal SIGCONT and wait for it to complete or
** stop.
** It waits for the job to report its status and then put the Shell
** back to foreground, letting the user enter a new command.
*/

int	s_bask_to_shell(t_sh *sh)
{
	int	ret;

	ret = ST_OK;
	if (tcsetpgrp(sh->fd, sh->pgid) == -1)
	{
		log_fatal("s_bask_to_shell: tcsetpgrp failed");
		ret = ST_TCSETPGRP;
	}
	if (tcsetattr(sh->fd, TCSADRAIN, &sh->termios_new) == -1)
	{
		log_fatal("s_bask_to_shell: tcsetattr failed");
		if (ret == ST_OK)
			ret = ST_TCSETATTR;
	}
	return (ST_OK);
}

int	job_foreground(t_sh *sh, t_job *j, int sigcont)
{
	log_debug("put job to foreground (id: %d, pgid: %d)", j->id, j->pgid);

	j->notified = 1;

	// make the job controlling the terminal
	if (tcsetpgrp(sh->fd, j->pgid) == -1)
	{
		if (errno != EINVAL)
		{
			// todo notify the user a problem occured
			log_error("failed to make the job %d controlling terminal", j->pgid);
			return (job_kill(sh, j, ST_TCSETPGRP));
		}
	}
	else if (sigcont == 1)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
		{
			// todo notify the user a problem occured
			log_error("failed to continue the stopped job %d", j->pgid);
			return (job_kill(sh, j, ST_SIGCONT));
		}
		if (tcgetattr(sh->fd, &j->tmodes) == -1)
		{
			log_error("failed to set terminal structure");
			return (job_kill(sh, j, ST_SIGCONT));
		}
	}
	job_wait(j);
	if (job_is_completed(j) == 0 && tcgetattr(sh->fd, &j->tmodes) != 0)
	{
		// todo notify user a problem occured
		log_error("failed to save termios structure a the job %d", j->pgid);
	}
	return (s_bask_to_shell(sh));
}

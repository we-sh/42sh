#include "shell.h"

/*
** This function put a given job into foreground, may restart a stopped job
** by sending to it the signal SIGCONT and wait for it to complete or
** stop.
** It waits for the job to report its status and then put the Shell
** back to foreground, letting the user enter a new command.
*/

int	s_bask_to_shell(t_sh *sh, t_job *j)
{
	// make the shell controlling the terminal
	if (tcsetpgrp(sh->fd, sh->pgid) == -1)
	{
		log_fatal("s_bask_to_shell: tcsetpgrp failed");
		return (job_kill(j, ST_TCSETPGRP));
	}

	// reset the termios structure to its previous state
	if (tcsetattr(sh->fd, TCSADRAIN, &sh->termios_new) == -1)
		return (job_kill(j, ST_TCSETATTR));

	return (ST_OK);
}

int	job_foreground(t_sh *sh, t_job *j, int sigcont)
{
	log_debug("put job to foreground (id: %d, pgid: %d)", j->id, j->pgid);

	// make the job controlling the terminal
	if (tcsetpgrp(sh->fd, j->pgid) == -1)
	{
		if (!(errno == EINVAL && (job_is_completed(j) == 1 || job_is_stopped(j) == 1)))
		{
			// todo notify the user a problem occured
			log_error("failed to set the stopped job %d", j->pgid);
		}
		return (s_bask_to_shell(sh, j));
	}

	// reset termios structure to its initial configuration
	if (tcsetattr(sh->fd, TCSADRAIN, &sh->termios_old) == -1)
		return (job_kill(j, ST_TCSETATTR));

	if (sigcont == 1)
	{
		// stopped job to continued job
		if (kill(-j->pgid, SIGCONT) < 0)
		{
			// todo notify the user a problem occured
			log_error("failed to continue the stopped job %d", j->pgid);
			return (s_bask_to_shell(sh, j));
		}
	}

	job_wait(j);

	// save termios structure when job is stopped but not completed
	// so that we can launch job again with its termios
	if (job_is_completed(j) == 0 && tcgetattr(sh->fd, &j->tmodes) != 0)
	{
		// todo notify user a problem occured
		log_error("failed to save termios structure a the job %d", j->pgid);
	}

	return (s_bask_to_shell(sh, j));
}

#include "shell.h"

/*
** This function put a given job into foreground, may restart a stopped job
** by sending to it the signal SIGCONT and wait for it to complete or
** stop.
** It waits for the job to report its status and then put the Shell
** back to foreground, letting the user enter a new command.
*/

int	job_foreground(t_job *j, int sigcont)
{
	// temporary
	int shell_pid = getpid();

	log_debug("put job to foreground (pgid: %d)", j->pgid);

	// make the job controlling the terminal
	if (tcsetpgrp(shell_fd(), j->pgid) == -1)
		shell_exit(ST_TCSETPGRP);

	// reset termios structure to its initial configuration
	//if ((ret = update_termios(TCSADRAIN, &g_sh->termios_backup)) != STATUS_OK)
	//	shell_exit(ret);
	if (sigcont == 1)
	{
		// stopped job to continued job
		if (kill(-j->pgid, SIGCONT) < 0)
		{
			perror ("kill (SIGCONT)");
			// todo error management
		}
	}
	while (job_is_completed(j) == 0);
	//while (is_job_completed(j) == 0 && is_job_stopped(j) == 0);

	// make the shell controlling the terminal
	if (tcsetpgrp(shell_fd(), shell_pid) == -1)
		shell_exit(ST_TCSETPGRP);

	// save termios structure when job is stopped but not completed
	// so that we can launch job again with its termios
	//if (is_job_completed(j) == 0 && tcgetattr(g_sh->fd, &j->termios) != 0)
	//	shell_exit(STATUS_TCGETATTR);

	// reset the termios structure to its previous state
	//if ((ret = update_termios(TCSADRAIN, &g_sh->termios)) != STATUS_OK)
	//	exit_sh(ret);

	return (ST_OK);
}

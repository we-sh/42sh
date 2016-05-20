#include "shell.h"

/*
** This function sets all signal handlers to SIG_IGN except for SIGCHLD.
** "When a shell enables job control, it should set itself to ignore all
** the job control stop signals so that it doesn’t accidentally stop itself"
*/

int	signal_to_ignore(void)
{
	if (signal(SIGCHLD, signal_sigchld) == SIG_ERR)
		return (ST_SIGNAL);
	// if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
	// 	return (ST_SIGNAL);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTTIN, SIG_IGN) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTTOU, SIG_IGN) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (ST_SIGNAL);
	return (ST_OK);
}

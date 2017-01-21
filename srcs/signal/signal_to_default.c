#include "shell.h"
#include <signal.h>

/*
** This function sets all signal handlers to SIG_DFL.
** It is called within each child process after `fork` to let the processes
** handle the signals in their own way.
*/

int	signal_to_default(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTTIN, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGTTOU, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
		return (ST_SIGNAL);
	return (ST_OK);
}

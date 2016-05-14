#include "shell.h"

int	signal_to_ignore(void)
{
	if (signal(SIGCHLD, signal_sigchld) == SIG_ERR)
		return (ST_SIGNAL);
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

#include "shell.h"

void	signal_sigtstp(int sig)
{
	static int	gpid = 0;

	if (sig < 0)
		gpid = sig;
	else
	{
		if (gpid != 0)
			kill(gpid, SIGTSTP);
	}
}

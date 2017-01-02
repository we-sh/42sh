#include "shell.h"

/*
** This function is attached to the signal SIGUSR1
** on all processes that get a piped standard output.
**
** For example: `base64 /dev/urandom | head -c 100`
** When the process `head` get terminated, a signal SIGUSR1
** is sent to the process `base64` to tell him it is no longer
** necessary to write into the pipe.
*/

void		signal_sigusr1(int sig)
{
	(void)sig;
	close(STDOUT_FILENO);
}

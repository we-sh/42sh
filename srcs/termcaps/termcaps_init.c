#include "shell.h"
#include <limits.h>
int			termcaps_init(t_sh *sh)
{
	if (!termcaps_termios_init(sh))
	{
		log_fatal("termcaps_termios_init() failed");
		return (0); //udpate return
	}
	return (1);
}

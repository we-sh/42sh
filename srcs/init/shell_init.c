#include "shell.h"

int				shell_init(t_sh *sh)
{
	int			ret;

	sh->pgid = getpid();
	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	if ((ret = shell_is_interactive()) < 0)
		return (-ret);
	if (shell_is_interactive() == 1)
	{
		if ((ret = shell_fd()) < 0)
			return (-ret);
		while (tcgetpgrp(STDIN_FILENO) != (sh->pgid = getpgrp()))
			kill(-sh->pgid, SIGTTIN);

		if ((ret = signal_to_ignore()) != ST_OK)
			return (ret);

		if (setpgid(sh->pgid, sh->pgid) < 0)
		{
			log_fatal("setpgid() failed.");
			return (ST_SETPGID);
		}
		log_info("pgid: %d", sh->pgid);
		if (tcsetpgrp(STDIN_FILENO, sh->pgid) < 0)
			return (ST_TCSETPGRP);
	}
	if (termcaps_init(sh) != ST_OK)
	{
 	 log_error("termcaps_init() failed"); 
	 return (-1);
	}
	return (ST_OK);
}

#include "shell.h"

int				shell_init(void)
{
	int			ret;
	int			sh_pgid;
	t_termios	sh_tmodes;

	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	if ((ret = shell_is_interactive()) < 0)
		return (-ret);
	if (shell_is_interactive() == 1)
	{
		if ((ret = shell_fd()) < 0)
			return (-ret);
		while (tcgetpgrp(STDIN_FILENO) != (sh_pgid = getpgrp()))
			kill(-sh_pgid, SIGTTIN);
		if ((ret = signal_to_ignore()) != ST_OK)
			return (ret);
		if (setpgid(sh_pgid, sh_pgid) < 0)
		{
			log_fatal("setpgid() failed.");
			return (ST_SETPGID);
		}
		log_info("pgid: %d", sh_pgid);
		if (tcsetpgrp(STDIN_FILENO, sh_pgid) < 0)
			return (ST_TCSETPGRP);
		tcgetattr(STDIN_FILENO, &sh_tmodes);
	}
	return (ST_OK);
}

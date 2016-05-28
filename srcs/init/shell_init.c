#include "shell.h"

/*
** This function is called at initialization, and then returns the actual
** terminal device file descriptor (tty).
** It returns a negative value when an error occurs.
*/

static int	shell_fd_init(t_sh *sh)
{
	char		*tty_name;

	sh->is_interactive = isatty(STDIN_FILENO);
	if (sh->is_interactive)
		log_info("interactive mode enabled");
	else
		log_warn("interactive mode disabled");
	if (sh->is_interactive == 0)
		sh->fd = STDOUT_FILENO;
	else
	{
		if ((tty_name = ttyname(STDIN_FILENO)) == NULL)
		{
			log_error("ttyname() failed");
			return (-1);
		}
		if ((sh->fd = open(tty_name, O_RDWR)) == -1)
		{
			log_error("open() failed");
			return (-1);
		}
		log_info("ttyname: %s, ttyslot: %d", tty_name, ttyslot());
	}
	log_info("actual tty fd: %d", sh->fd);
	return (ST_OK);
}

int		shell_init(t_sh *sh)
{
	int		ret;

	sh->pgid = getpid();
	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	if (shell_fd_init(sh) != ST_OK)
	{
		log_error("shell_fd_init() failed");
		return (-1);
	}
	if (sh->is_interactive)
	{
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
	return (ST_OK);
}

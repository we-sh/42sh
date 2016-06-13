#include "shell.h"

/*
** This function is called at initialization, and then returns the actual
** terminal device file descriptor (tty).
** It returns a negative value when an error occurs.
*/

static int	s_shell_fd_init(t_sh *sh)
{
	int			fd;
	char		*tty_name;

	fd = -1;
	if (sh->is_interactive == true)
	{
		if ((tty_name = ttyname(STDIN_FILENO)) == NULL)
		{
			log_error("ttyname() failed");
			return (ST_TTYNAME);
		}
		if ((fd = open(tty_name, O_RDWR)) == -1)
		{
			log_error("open() failed");
			return (ST_OPEN);
		}
		log_info("ttyname: %s, ttyslot: %d", tty_name, ttyslot());
	}
	else
		fd = STDIN_FILENO;
	sh->fd = fd;
	log_info("is_interactive ? %s fd: %d", sh->is_interactive ? "true" : "false", fd);
	return (ST_OK);
}

int		shell_init(t_sh *sh, char *envp[])
{
	int		ret;

	INIT_LIST_HEAD(&g_current_jobs_list_head);
	sh->last_exit_status = 0;
	sh->pgid = getpid();
	/* env */
	environment_init(sh, envp);
	path_init_hasht(sh);
	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	if ((ret = s_shell_fd_init(sh)) != ST_OK)
	{
		log_error("s_shell_fd_init() failed");
		return (ret);
	}
	if (sh->is_interactive == true)
	{
		/* jobs */
		while (tcgetpgrp(STDIN_FILENO) != (sh->pgid = getpgrp()))
		{
			if (kill(-sh->pgid, SIGTTIN) != 0)
			  log_error("kill(-sh->pgid. SIGTTIN) failed");
		}
		if ((ret = signal_to_ignore()) != ST_OK)
			return (ret);
		if (setpgid(sh->pgid, sh->pgid) < 0)
			return (ST_SETPGID);
		log_info("pgid: %d", sh->pgid);

		if (tcsetpgrp(STDIN_FILENO, sh->pgid) < 0)
			return (ST_TCSETPGRP);

		/* termcaps */
		if (!termcaps_init(sh))
			return (ST_TERMCAPS_INIT);
	}
	return (ST_OK);
}

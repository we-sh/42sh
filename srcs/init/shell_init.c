# include "shell.h"

static void		s_signal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

int				shell_init(void)
{
	int			ret;
	int			sh_pgid;
	t_termios	sh_tmodes;

	if ((ret = shell_is_interactive()) < 0)
		return (-ret);
	if (shell_is_interactive() == 1)
	{
		if ((ret = shell_fd()) < 0)
			return (-ret);
		while (tcgetpgrp(STDIN_FILENO) != (sh_pgid = getpgrp()))
			kill(-sh_pgid, SIGTTIN);
		s_signal_handler();
		if (setpgid(sh_pgid, sh_pgid) < 0)
		{
			log_fatal("setpgid() failed.\n");
			return (ST_SETPGID);
		}
		log_info("pgid: %d\n", sh_pgid);
		if (tcsetpgrp(STDIN_FILENO, sh_pgid) < 0)
			return (ST_TCSETPGRP);
		tcgetattr(STDIN_FILENO, &sh_tmodes);
	}
	return (0);
}

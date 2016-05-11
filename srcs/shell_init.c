# include "shell.h"

static void	s_signal_handler(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

static int	s_shell_is_interactive(int fd)
{
	int is_inter = isatty(fd);

	log_warn("%s interactive\n", is_inter ? "is" : "is NOT");
	log_info("ttyname: %s, ttyslot: %d\n", ttyname(fd), ttyslot());
	return (is_inter);
}

int			shell_init(void)
{
	int			sh_pgid;
	t_termios	sh_tmodes;

	if (s_shell_is_interactive(STDIN_FILENO))
	{
		while (tcgetpgrp(STDIN_FILENO) != (sh_pgid = getpgrp()))
			kill(-sh_pgid, SIGTTIN);
		s_signal_handler();
		if (setpgid(sh_pgid, sh_pgid))
		{
			log_fatal("setpgid() failed.\n");
			return (ST_SETPGID);
		}
		log_info("pgid: %d\n", sh_pgid);
		tcsetpgrp(STDIN_FILENO, sh_pgid);
		tcgetattr(STDIN_FILENO, &sh_tmodes);
	}
	else
	{
		/* define what to do */
	}
	return (0);
}

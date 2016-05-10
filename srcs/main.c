#include "shell.h"

/*
** TODO: Implement better signal handler
*/

static void	signal_init(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
}

/*
** isatty() check if shell is interactive
** Then we put ourselves in our own process group,
** and loop until we are in the foreground.
** tcsetpgrp() grab control of the terminal.
** tcgetattr() save default terminal attr for shell.
*/

static int	shell_init(void)
{
	int			sh_pgid;
	int			sh_fd;
	t_termios	sh_tmodes;

	sh_fd = STDIN_FILENO;
	if (isatty(sh_fd))
	{
		while (tcgetpgrp(sh_fd) != (sh_pgid = getpgrp()))
			kill(-sh_pgid, SIGTTIN);
		log_info("pgid %d pgrp %d\n", sh_pgid, getpgrp());
		signal_init();
		if (setpgid(sh_pgid, sh_pgid))
		{
			log_fatal("setpgid() failed.\n");
			return (ST_SETPGID);
		}
		log_info("shell pgid: %d\n", sh_pgid);
		tcsetpgrp(sh_fd, sh_pgid);
		tcgetattr(sh_fd, &sh_tmodes);
		return (0);
	}
	return (-1);
}

int			main(int ac, const char *av[])
{
	(void)av;
	(void)ac;
	logger_init(D_TRACE, "out.log");
	if (shell_init())
	{
		log_fatal("shell_init() failed.");
		return (-1);
	}
	stdin_loop();
	logger_close();
	return (0);
}

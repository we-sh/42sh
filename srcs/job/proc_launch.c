#include "shell.h"

static int	s_signal_handler(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	return (ST_OK);
}

void		proc_launch(t_job *j, t_proc *p)
{
	pid_t pgid;

	if (shell_is_interactive())
	{
		p->pid = getpid();
		pgid = j->pgid;
		if (pgid == 0)
			pgid = p->pid;
		setpgid(p->pid, pgid);
		// if (j->foreground == 1)
		// 	tcsetpgrp(FILE DESCRIPTOR TTY, pgid);
		s_signal_handler();
	}

	if (p->stdin != STDIN_FILENO)
	{
		dup2(p->stdin, STDIN_FILENO);
		close(p->stdin);
	}
	if (p->stdout != STDOUT_FILENO)
	{
		dup2(p->stdout, STDOUT_FILENO);
		close(p->stdout);
	}
	if (p->stderr != STDERR_FILENO)
	{
		dup2(p->stderr, STDERR_FILENO);
		close(p->stderr);
	}

	// built-in body callback here
	execvp(p->argv[0], p->argv);
	// show error
	exit(EXIT_FAILURE);
}

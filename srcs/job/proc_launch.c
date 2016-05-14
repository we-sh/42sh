#include "shell.h"

void		proc_launch(t_job *j, t_proc *p)
{
	pid_t pgid;

	if (shell_is_interactive() == 1)
	{
		p->pid = getpid();
		pgid = j->pgid;
		if (pgid == 0)
			pgid = p->pid;
		setpgid(p->pid, pgid);
		// if (j->foreground == 1)
		// 	tcsetpgrp(FILE DESCRIPTOR TTY, pgid);
		signal_to_default();
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

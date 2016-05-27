#include "shell.h"

/*
** This function is the entry point of a child process (freshly forked).
*/

void		proc_launch(t_sh *sh, t_job *j, t_proc *p)
{
	pid_t	pgid;

	p->pid = getpid();
	if (shell_is_interactive() == 1)
	{
		pgid = j->pgid;
		if (pgid == 0)
			pgid = p->pid;
		setpgid(p->pid, pgid);
		if (j->foreground == 1)
			tcsetpgrp(shell_fd(), pgid);
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

	builtin_callback(BLTIN_CB_EXEC, sh, p);
	execvp(p->argv[0], p->argv);
	// show error
	exit(EXIT_FAILURE);
}

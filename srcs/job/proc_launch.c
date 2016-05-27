#include "shell.h"

/*
** This function is the entry point of a child process (freshly forked).
*/

void		proc_launch(t_job *j, t_proc *p)
{
	pid_t pgid;

	if (shell_is_interactive() == 1)
	{
		p->pid = getpid();
		pgid = j->pgid;
		if (pgid == 0)
			pgid = p->pid;
		if (setpgid(p->pid, pgid) != 0)
		{
			perror("setgid");
			return ;
		}
		if (j->foreground == 1)
			tcsetpgrp(shell_fd(), pgid);
		signal_to_default();
	}

	if (p->stdin != STDIN_FILENO)
	{
		if (dup2(p->stdin, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return ;
		}
		if (close(p->stdin) != 0)
		{
			perror("close");
			return ;
		}
	}
	if (p->stdout != STDOUT_FILENO)
	{
		if (dup2(p->stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return ;
		}
		if (close(p->stdout) != 0)
		{
			perror("close");
			return ;
		}
	}
	if (p->stderr != STDERR_FILENO)
	{
		if (dup2(p->stderr, STDERR_FILENO))
		{
			perror("dup2");
			return ;
		}
		if (close(p->stderr))
		{
			perror("close");
			return ;
		}
	}

	// built-in body callback here
	if (execvp(p->argv[0], p->argv) == -1)
	{
		perror("execvp");
		return ;
	}
	// show error
	exit(EXIT_FAILURE);
}

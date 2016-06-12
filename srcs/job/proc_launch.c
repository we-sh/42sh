#include "shell.h"

/*
** This function is the entry point of a child process (freshly forked).
*/

void		proc_launch(t_sh *sh, t_job *j, t_proc *p)
{
	// char	*absolute_path;

	// absolute_path = NULL;
	p->pid = getpid();
	if (sh->is_interactive == 1)
	{
		if (j->pgid == 0)
			j->pgid = p->pid;
		if (setpgid(p->pid, j->pgid) == -1)
		{
			//log_fatal("setpgid(%d, %d) error: %s", p->pid, j->pgid, strerror(errno));
			//exit(EXIT_FAILURE);
		}
		if (j->foreground == 1)
			if (tcsetpgrp(sh->fd, j->pgid) == -1)
			{

			}
		if (signal_to_default() != ST_OK)
		{
			log_fatal("signal_to_default error (pid: %d)", p->pid);
			exit(EXIT_FAILURE);
		}
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
	

	/*
	*	OLD PATH FINDER
	*	absolute_path = path_finder(sh, p->argv[0]);
	*/
	if (path_hash_finder(sh, p->argv[0]) == ST_OK)
		execve(p->argv[0], p->argv, sh->envp);
	exit(EXIT_FAILURE);
}

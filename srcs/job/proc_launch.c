#include "shell.h"

void	proc_launch(t_job *j, t_proc *p)
{
	//pid_t				gpid;

	//if (interactive mode)
	//{
	//	p->pid = getpid();
	//	gpid = j->gpid;
	//	if (gpid == 0)
	//		gpid = p->pid;
	//	setpgid(p->pid, gpid);
	//	//if (j->foreground == 1)
	//	//	tcsetpgrp(FILE DESCRIPTOR TTY, gpid);
	//	signal (SIGINT, SIG_DFL);
	//	signal (SIGQUIT, SIG_DFL);
	//	signal (SIGTSTP, SIG_DFL);
	//	signal (SIGTTIN, SIG_DFL);
	//	signal (SIGTTOU, SIG_DFL);
	//	signal (SIGCHLD, SIG_DFL);
	//}

	(void)j;

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

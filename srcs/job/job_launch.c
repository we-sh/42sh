#include "shell.h"

/*
** This function takes a job t_job as argument and iterates
** on its process list to launch them sequentially.
** It handles pipes and redirections.
*/

static int			s_fork_it(t_sh *sh, t_job *j, t_proc *p)
{
	int	ret;

	if ((ret = builtin_callback(BLTIN_CB_BEFORE, sh, p)) != ST_OK)
		return (job_kill(j, ret));
	p->pid = fork();
	if (p->pid < 0)
	{
		log_error("fork failed (%d)", p->pid);
		return (job_kill(j, ST_FORK));
	}
	else if (p->pid == 0)
		proc_launch(sh, j, p);
	else
	{
		if (sh->is_interactive)
		{
			if (j->pgid == 0)
				j->pgid = p->pid;
			if (j->pgid == p->pid && setpgid(p->pid, j->pgid) < 0)
			{
				log_fatal("setpgid(%d, %d) error: %s", p->pid, j->pgid, strerror(errno));
				return (job_kill(j, ST_SETPGID));
			}
		}
	}
	return (ST_OK);
}

int					job_launch(t_sh *sh, t_job *j)
{
	int				ret;
	t_list			*pos;
	t_list			*head;
	t_proc			*p;
	int				job_pipe[2];
	int				outputs[3];
	int 			exit_status;

	log_info("launching job `%s`", j->command);
	job_pipe[0] = -1;
	outputs[STDIN_FILENO] = j->stdin;
	outputs[STDERR_FILENO] = j->stderr;
	head = &j->proc_head;
	pos = head;
	LIST_FOREACH(head, pos)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		if (pos->next != head)
		{
			if (pipe(job_pipe) < 0)
				return (job_kill(j, ST_PIPE));
			outputs[STDOUT_FILENO] = job_pipe[STDOUT_FILENO];
		}
		else
			outputs[STDOUT_FILENO] = j->stdout;

		p->stdin = outputs[STDIN_FILENO];
		p->stdout = outputs[STDOUT_FILENO];
		p->stderr = outputs[STDERR_FILENO];
		if ((ret = s_fork_it(sh, j, p)) != ST_OK)
			return(job_kill(j, ret));

		if (outputs[STDIN_FILENO] != j->stdin)
			close(outputs[STDIN_FILENO]);
		if (outputs[STDOUT_FILENO] != j->stdout)
			close(outputs[STDOUT_FILENO]);
		outputs[STDIN_FILENO] = job_pipe[0];

		// useful if we need to keep last process alive:
		//if (p->next == NULL)
		//	break ;
	}
	if (!sh->is_interactive)
	{
		job_wait(j);
	//	after callback built-in
	}
	else if (j->foreground == 1)
	{
		exit_status = job_foreground(sh, j, 0);
		if (exit_status != ST_OK)
		  return (exit_status);
	//	put job to foreground
	//	after callback built-in
	}
	//else
	//	put job to background
	//	return here to avoid builtin callback

	if ((pos = list_nth(head, -1)) != head)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		if ((ret = builtin_callback(BLTIN_CB_AFTER, sh, p)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

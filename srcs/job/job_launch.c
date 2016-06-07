#include "shell.h"

/*
** This function takes a job t_job as argument and iterates
** on its process list to launch them sequentially.
** It handles pipes and redirections.
*/

static int			s_fork_it(t_sh *sh, t_job *j, t_proc *p)
{
	int	ret;

	if ((ret = env_update_from_cmd_line(&p->argv, &p->argc, &p->envp)) != ST_OK)
		return (job_kill(sh, j, ret));
	if ((ret = builtin_callback(BLTIN_CB_BEFORE, sh, p)) != ST_OK)
		return (job_kill(sh, j, ret));
	p->pid = fork();
	if (p->pid < 0)
	{
		log_error("fork failed (%d)", p->pid);
		return (job_kill(sh, j, ST_FORK));
	}
	else if (p->pid == 0)
	{
		proc_launch(sh, j, p);
	}
	else
	{
		if (sh->is_interactive == 1)
		{
			if (j->pgid == 0)
				j->pgid = p->pid;
			if (setpgid(p->pid, j->pgid) < 0)
			{
				errno = 0;
				if (waitpid(p->pid, NULL, WNOHANG) && errno != ECHILD)
				{
					return (job_kill(sh, j, ST_SETPGID));
				}
			}
		}
	}
	return (ST_OK);
}

static int			s_job_setup(t_sh *sh, t_job *job)
{
	t_list	*head;
	t_list	*pos;
	t_proc	*proc;
	int		job_pipe[2];
	int		ret;

	int in = job->stdin;
	int out = job->stdout;
	int err = job->stderr;
	(void)err;

	head = &job->proc_head;
	LIST_FOREACH(head, pos)
	{
		proc = CONTAINER_OF(pos, t_proc, list_proc);

		if (pos->next != head)
		{
			if (pipe(job_pipe) < 0)
				return (job_kill(sh, job, ST_PIPE));
			out = job_pipe[1];
		}
		else
			out = job->stdout;

		if (proc->stdin == job->stdin)
		{
			proc->stdin = in;
		}

		if (proc->stdout == job->stdout)
		{
			proc->stdout = out;
		}

		if (proc->stderr == job->stderr)
		{
			proc->stderr = err;
		}

		ret = s_fork_it(sh, job, proc);
		if (ret != ST_OK)
			return (job_kill(sh, job, ret));

		if (in != job->stdin)
			close(in);
		if (out != job->stdout)
			close(out);
		if (err != job->stderr)
			close(err);
		in = job_pipe[0];

		// useful if we need to keep last process alive:
		//if (p->next == NULL)
		//	break ;
	}

	return (ST_OK);
}

int					job_launch(t_sh *sh, t_job *j)
{
	int		ret;
	t_list	*head;
	t_list	*pos;
	t_proc	*p;

	log_info("launching job `%s`", j->command);

	ret = s_job_setup(sh, j);
	if (ret != ST_OK)
		return (ret);

	if (sh->is_interactive == 0)
		job_wait(j);
	else if (j->foreground == 1)
	{
		ret = job_foreground(sh, j, 0);
		if (ret != ST_OK)
		  return (ret);
	}
	else
		return (job_background(j, 0));

	head = &j->proc_head;
	if ((pos = list_nth(head, -1)) != head)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		sh->last_exit_status = p->exit_status;
		if ((ret = builtin_callback(BLTIN_CB_AFTER, sh, p)) != ST_OK)
			return (ret);
	}

	return (ST_OK);
}

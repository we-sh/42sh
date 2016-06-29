/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_launch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function takes a job t_job as argument and iterates
** on its process list to launch them sequentially.
** It handles pipes and redirections.
*/

static int			s_fork_it(t_sh *sh, t_job *j, t_proc *p)
{
	int		ret;

	if ((p->envp = ft_array_dup(sh->envp)) == NULL)
		return (ST_MALLOC);
	if ((ret = env_update_from_cmd_line(&p->argv, &p->argc, &p->envp)) != ST_OK)
		return (ret);
	if ((ret = builtin_callback(BLTIN_CB_BEFORE, sh, p)) != ST_OK)
		return (ret);
	p->pid = fork();
	if (p->pid < 0)
		return (ST_FORK);
	else if (p->pid == 0)
		proc_launch(sh, j, p);
	else if (sh->is_interactive == 1)
	{
		if (j->pgid == 0)
			j->pgid = p->pid;
		if (setpgid(p->pid, j->pgid) < 0)
		{
			errno = 0;
			if (waitpid(p->pid, NULL, WNOHANG) && errno != ECHILD)
				return (ST_SETPGID);
		}
	}
	return (ST_OK);
}

static int			s_proc_setup(t_proc *proc, t_sh *sh, t_list *head, int *fds)
{
	int		ret;

	fds[FD_STDERR] = proc->stderr;
	if (proc->list_proc.next != head)
	{
		if (pipe(fds) < 0)
			return (ST_PIPE);
		fds[FD_STDOUT] = fds[FD_PIPE_OUT];
	}
	else
		fds[FD_STDOUT] = proc->stdout;
	if (proc->list_proc.prev == head)
		fds[FD_STDIN] = proc->stdin;
	if (proc->stdin == proc->j->stdin)
		proc->stdin = fds[FD_STDIN];
	if (proc->stdout == proc->j->stdout)
		proc->stdout = fds[FD_STDOUT];
	if (proc->stderr == proc->j->stderr)
		proc->stderr = fds[FD_STDERR];
	if ((ret = s_fork_it(sh, proc->j, proc)) != ST_OK)
		return (ret);
	return (ST_OK);
}

static int			s_job_setup(t_sh *sh, t_job *job)
{
	t_list	*head;
	t_list	*pos;
	int		ret;
	int		fds[5];

	head = &job->proc_head;
	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		if ((ret = s_proc_setup(CONTAINER_OF(pos, t_proc, list_proc),
			sh, head, fds)) != ST_OK)
			return (ret);
		if (fds[FD_STDIN] != STDIN_FILENO && fds[FD_STDIN] != STDOUT_FILENO
											&& fds[FD_STDIN] != STDERR_FILENO)
			close(fds[FD_STDIN]);
		if (fds[FD_STDOUT] != STDIN_FILENO && fds[FD_STDOUT] != STDOUT_FILENO
											&& fds[FD_STDOUT] != STDERR_FILENO)
			close(fds[FD_STDOUT]);
		if (fds[FD_STDERR] != STDIN_FILENO && fds[FD_STDERR] != STDOUT_FILENO
											&& fds[FD_STDERR] != STDERR_FILENO)
			close(fds[FD_STDERR]);
		fds[FD_STDIN] = fds[FD_PIPE_IN];
	}
	return (ST_OK);
}

static int			s_leave_job_launch(t_sh *sh, t_job *j)
{
	t_list	*head;
	t_list	*pos;
	t_proc	*p;
	int		ret;

	head = &j->proc_head;
	if ((pos = list_nth(head, -1)) != head)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		sh->last_exit_status = p->exit_status;
		j->exit_status = p->exit_status;
		if ((ret = builtin_callback(BLTIN_CB_AFTER, sh, p)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

int					job_launch(t_sh *sh, t_job *j)
{
	int		ret;

	log_info("launching job `%s`", j->command);
	j->launched = 1;
	ret = s_job_setup(sh, j);
	if (ret != ST_OK)
		return (job_kill(sh, j, ret));
	if (sh->is_interactive == 0)
	{
		j->foreground = 1;
		job_wait(j);
	}
	else if (j->foreground == 0)
		return (job_background(sh, j, 0));
	else if ((ret = job_foreground(sh, j, 0)) != ST_OK)
		return (ret);
	return (s_leave_job_launch(sh, j));
}

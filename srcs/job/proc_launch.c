#include "shell.h"

/*
** This function is the entry point of a child process (freshly forked).
*/

static int	s_interactive_mode_callback(t_sh *sh, t_job *j, t_proc *p)
{
	if (sh->is_interactive == 1)
	{
		if (j->pgid == 0)
			j->pgid = p->pid;
		if (setpgid(p->pid, j->pgid) == -1)
		{
			log_warn("setpgid(%d, %d) errno: %d", p->pid, j->pgid, errno);
		}
		if (j->foreground == 1)
			if (ioctl(sh->fd, TIOCSPGRP, &j->pgid) == -1)
			{
				log_warn("setpgid(%d, %d) errno: %d", p->pid, j->pgid, errno);
			}
		if (signal_to_default() != ST_OK)
		{
			log_fatal("signal_to_default error (pid: %d)", p->pid);
			exit(EXIT_FAILURE);
		}
	}
	return (ST_OK);
}

static int	s_dup2_and_close(int from, int to)
{
	if (to != from)
	{
		if (to == -1)
			close(from);
		else
		{
			dup2(to, from);
			if (!(to == STDERR_FILENO && from == STDOUT_FILENO)
				&& !(to == STDOUT_FILENO && from == STDERR_FILENO))
				close(to);
		}
	}
	return (ST_OK);
}

static int	s_add_color_to_cmd(t_proc *p)
{
	char	*value;

	value = NULL;
	if (ft_strcmp("ls", p->argv[0]) == 0)
		value = LSOPTCOLOR;
	else if (ft_strcmp("grep", p->argv[0]) == 0)
		value = "--color=auto";
	if (p->argc > 1)
		ft_array_push_index(&p->argv, value, 1);
	else
		ft_array_push_back(&p->argv, value);
	return (ST_OK);
}

static int	s_proc_launch_execve(t_proc *p)
{
	char	*lowerargv;
	char	*match;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if ((match = ft_strdup(p->argv[0])) == NULL)
		return (ST_MALLOC);
	if (ft_strncmp(match, "/", 1) != 0 && ft_strncmp(match, ".", 1) != 0)
		lowerargv = ft_strtolower(match);
	else
		lowerargv = match;
	if ((ret = path_hash_finder(p->envp, &lowerargv)) == ST_OK)
	{
		if ((conf_check_color_mode(p->envp) == ST_OK))
			s_add_color_to_cmd(p);
		if ((execve(lowerargv, p->argv, p->envp)) == -1)
			return (ST_OK);
	}
	else
		return (ret);
	free(lowerargv);
	return (ST_OK);
}

void		proc_launch(t_sh *sh, t_job *j, t_proc *p)
{
	int		ret;

	ret = 0;
	p->pid = getpid();
	s_interactive_mode_callback(sh, j, p);
	s_dup2_and_close(STDIN_FILENO, p->stdin);
	if (p->stdout == STDERR_FILENO)
	{
		s_dup2_and_close(STDERR_FILENO, p->stderr);
		s_dup2_and_close(STDOUT_FILENO, p->stdout);
	}
	else
	{
		s_dup2_and_close(STDOUT_FILENO, p->stdout);
		s_dup2_and_close(STDERR_FILENO, p->stderr);
	}
	if (p->is_valid == 1 && p->argc == 0)
		p->is_valid = 0;
	if (p->is_valid != 1)
		exit(p->is_valid == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	builtin_callback(BLTIN_CB_EXEC, sh, p);
	if ((ret = (s_proc_launch_execve(p))) != ST_OK)
		display_status(ret, p->argv[0], NULL);
	exit(EXIT_FAILURE);
}

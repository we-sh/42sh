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

static int	s_match_one_binary(char *str)
{
	if (ft_strcmp("/bin/ls", str) == 0)
		return (ST_OK);
	else if (ft_strcmp("/bin/grep", str) == 0)
		return (ST_OK);
	return (-1);
}

static int	s_proc_launch_execve(t_sh *sh, t_proc *p)
{
	char	*lowerargv;
	int		i;

	i = 0;
	lowerargv = ft_strtolower(p->argv[0]);
	if (path_hash_finder(sh->envp, &lowerargv) == ST_OK)
	{
		 if ((s_match_one_binary(lowerargv) == ST_OK) && (conf_check_color_mode()) == ST_OK)
		 {
			while(p->argv[i])
				i++;
			if ((p->argv[i++] = ft_strdup("--color=auto")) == NULL)
				return (ST_MALLOC);
			p->argv[i] = NULL;
		 }
		if ((execve(lowerargv, p->argv, p->envp)) == -1)
			return (ST_OK);
	}
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
	log_debug("argc:%d is_valid:%d", p->argc, p->is_valid);
	if (p->is_valid == 1 && p->argc == 0)
		p->is_valid = 0;
	if (p->is_valid != 1)
		exit(p->is_valid == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
	builtin_callback(BLTIN_CB_EXEC, sh, p);
	if ((ret = (s_proc_launch_execve(sh, p))) != ST_OK)
		display_status(ret, NULL, NULL);
	exit(EXIT_FAILURE);
}

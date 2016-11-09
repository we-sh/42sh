#include "shell.h"

/*
** This function is called at initialization, and then returns the actual
** terminal device file descriptor (tty).
** It returns a negative value when an error occurs.
*/

static int	s_shell_environment(t_sh *sh, char *envp[])
{
	int ret;

	if ((ret = shell_environment(sh, envp)) != ST_OK)
		return (ret);
	path_init_hasht(sh->envp);
	if ((ret = conf_file_init(sh->envp)) != ST_OK)
		return (ret);
	if ((sh->pwd = getcwd(NULL, 0)) == NULL)
		return (ST_GETCWD);
	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	return (ST_OK);
}

static int	s_shell_fd_init(t_sh *sh)
{
	int			fd;
	char		*tty_name;

	fd = -1;
	if (sh->is_interactive == 1)
	{
		if ((tty_name = ttyname(STDIN_FILENO)) == NULL)
			return (ST_TTYNAME);
		if ((fd = open(tty_name, O_RDWR)) == -1)
			return (ST_OPEN);
	}
	else
		fd = STDIN_FILENO;
	sh->fd = fd;
	return (ST_OK);
}

static int	s_shell_job_control(t_sh *sh)
{
	int ret;

	while (1)
	{
		ioctl(STDIN_FILENO, TIOCGPGRP, &ret);
		if (ret == (sh->pgid = getpgrp()))
			break ;
		kill(-sh->pgid, SIGTTIN);
	}
	if ((ret = signal_to_ignore()) != ST_OK)
		return (ret);
	//let's keep these two lines just in case :-) (@jgigault)
	//if (setpgid(sh->pgid, sh->pgid) < 0)
	//	return (ST_SETPGID);
	if (ioctl(STDIN_FILENO, TIOCSPGRP, &sh->pgid) < 0)
		return (ST_TCSETPGRP);
	return (ST_OK);
}

static int	s_shell_termcaps(t_sh *sh)
{
	char	*prompt;

	if (!caps__initialize(sh->fd))
		return (ST_TERMCAPS_INIT);
	if ((prompt = shell_set_prompt(sh)) == NULL)
		return (ST_MALLOC);
	if (!termcaps_initialize(sh, prompt, &sh->termcaps_context))
	{
		free(prompt);
		return (ST_TERMCAPS_INIT);
	}
	if ((conf_check_color_mode(sh->envp)) == ST_OK)
		sh->termcaps_context.prompt.size = ft_strlen(prompt) -
	(ANSI_COLOR_LIGHT_BLUE_SIZE + ANSI_COLOR_RESET_SIZE);
	free(prompt);
	return (ST_OK);
}

int			shell_init(t_sh *sh, char *envp[])
{
	int		ret;

	INIT_LIST_HEAD(&g_current_jobs_list_head);
	INIT_LIST_HEAD(&sh->redir_head);
	sh->local_vars = NULL;
	sh->last_exit_status = 0;
	sh->pgid = getpid();
	if ((ret = s_shell_environment(sh, envp)) != ST_OK)
		return (ret);
	if ((ret = s_shell_fd_init(sh)) != ST_OK)
		return (ret);
	if (sh->is_interactive == 1)
	{
		if ((ret = s_shell_job_control(sh)) != ST_OK)
			return (ret);
		if ((ret = s_shell_termcaps(sh)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

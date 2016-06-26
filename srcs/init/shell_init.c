#include "shell.h"

/*
** This function is called at initialization, and then returns the actual
** terminal device file descriptor (tty).
** It returns a negative value when an error occurs.
*/

static int	s_shell_fd_init(t_sh *sh)
{
	int			fd;
	char		*tty_name;

	fd = -1;
	if (sh->is_interactive == true)
	{
		if ((tty_name = ttyname(STDIN_FILENO)) == NULL)
		{
			log_error("ttyname() failed");
			return (ST_TTYNAME);
		}
		if ((fd = open(tty_name, O_RDWR)) == -1)
		{
			log_error("open() failed");
			return (ST_OPEN);
		}
		log_info("ttyname: %s, ttyslot: %d", tty_name, ttyslot());
	}
	else
		fd = STDIN_FILENO;
	sh->fd = fd;
	log_info("is_interactive ? %s fd: %d",
		sh->is_interactive ? "true" : "false", fd);
	return (ST_OK);
}

int			shell_init(t_sh *sh, char *envp[])
{
	int		ret;
	char	*prompt;

	INIT_LIST_HEAD(&g_current_jobs_list_head);
	INIT_LIST_HEAD(&sh->redir_head);
	sh->last_exit_status = 0;
	sh->pgid = getpid();
	/* env */
	if ((ret = shell_environment(sh, envp)) != ST_OK)
		return (ret);
	path_init_hasht(sh->envp);
	if ((ret = conf_file_init(sh->envp)) != ST_OK)
		return (ret);
	if ((sh->pwd = getcwd(NULL, 0)) == NULL)
		return (ST_MALLOC);

	if ((ret = shell_language(LANG_EN)) < 0)
		return (-ret);
	if ((ret = s_shell_fd_init(sh)) != ST_OK)
	{
		log_error("s_shell_fd_init() failed");
		return (ret);
	}
	if (sh->is_interactive == 1)
	{
		/* jobs */
		while (1)
		{
			ioctl(STDIN_FILENO, TIOCGPGRP, &ret);
			if (ret == (sh->pgid = getpgrp()))
				break ;
			if (kill(-sh->pgid, SIGTTIN) != 0)
			  log_error("kill(-sh->pgid. SIGTTIN) failed");
		}
		if ((ret = signal_to_ignore()) != ST_OK)
			return (ret);
		if (setpgid(sh->pgid, sh->pgid) < 0)
			return (ST_SETPGID);
		log_info("pgid: %d", sh->pgid);

		if (ioctl(STDIN_FILENO, TIOCSPGRP, &sh->pgid) < 0)
			return (ST_TCSETPGRP);
		/* termcaps */
		if (!caps__initialize(sh->fd))
		{
			log_fatal("caps__initialize() failed");
			return (ST_TERMCAPS_INIT);
		}
		prompt = shell_set_prompt(sh->envp);
		if (!termcaps_initialize(sh, prompt, &sh->termcaps_context))
		{
			free(prompt);
			return (ST_TERMCAPS_INIT);
		}
		free(prompt);
	}
	return (ST_OK);
}

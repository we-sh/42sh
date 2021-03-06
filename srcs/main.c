#include "shell.h"
#include "libftprintf.h"

t_list		g_current_jobs_list_head = {
	.next = &g_current_jobs_list_head,
	.prev = &g_current_jobs_list_head
};

static int	s_usage(int status)
{
	int		fd;

	fd = status == ST_OK ? STDOUT_FILENO : STDERR_FILENO;
	if (status != ST_OK)
		ft_printf("%r%s: %s\n", fd,
			PROGRAM_NAME,
			i18n_translate(status));
	ft_printf("%r%s: %s\n", fd,
		i18n_translate(ST_USAGE),
		PROGRAM_NAME);
	return (EXIT_SUCCESS);
}

void		s_interactive_mode(t_sh *sh)
{
	if (sh->is_interactive == 1)
	{
		if (!history_write(sh->envp, &sh->termcaps_context.history, 0))
			display_status(ST_HISTORY, NULL, NULL);
		if (!termcaps_finalize(&sh->termcaps_context))
			exit(display_status(ST_TERMCAPS_FINALIZE, NULL, NULL));
		if (close(sh->fd) != 0)
			exit(display_status(ST_CLOSE, NULL, NULL));
		caps__finalize();
	}
}

int			main(int argc, char *argv[], char *envp[])
{
	int		ret;
	t_sh	sh;

	logger_init(D_TRACE, "/tmp/out.log");
	if ((sh.argv = ft_array_dup(argv)) == NULL)
		return (display_status(ST_MALLOC, NULL, NULL));
	if (argc > 1)
		return (s_usage(ST_EINVAL));
	if ((ret = option_parse(&sh.opt_head, g_sh_options, &sh.argv, 1)) != ST_OK)
		return (s_usage(ret));
	if (option_is_set(&sh.opt_head, ST_OPTION_HELP) == 1)
		return (s_usage(ST_OK));
	sh.is_interactive = isatty(STDIN_FILENO);
	if ((ret = shell_init(&sh, envp)) != ST_OK)
		exit(display_status(ret, NULL, NULL));
	if ((ret = loop_main(&sh)) != ST_END_OF_INPUT && ret != ST_EXIT)
		exit(display_status(ret, NULL, NULL));
	s_interactive_mode(&sh);
	logger_close();
	return (sh.last_exit_status);
}

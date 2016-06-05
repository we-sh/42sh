#include "shell.h"

t_list	g_current_jobs_list_head = {
	.next = &g_current_jobs_list_head,
	.prev = &g_current_jobs_list_head
};

static t_option				g_sh_option_help = {
	.name = "help",
	.index = ST_OPTION_HELP,
	.is_single_char = 0,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_sh_option_c = {
	.name = "c",
	.index = ST_OPTION_C,
	.is_single_char = 1,
	.has_value = 1,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_sh_options[] = {
	[0] = &g_sh_option_help,
	[1] = &g_sh_option_c,
	[2] = NULL
};

static int	s_usage(int status)
{
	int	fd;
	int	i;

	fd = status == ST_OK ? STDOUT_FILENO : STDERR_FILENO;
	if (status != ST_OK)
		ft_printf("%r%s: %s\n", fd,
			PROGRAM_NAME,
			i18n_translate(status));
	ft_printf("%r%s: %s [--help] [-c STRING]\n%s\n", fd,
		i18n_translate(ST_USAGE),
		PROGRAM_NAME,
		i18n_translate(ST_OPTIONS));
	i = 0;
	while (g_sh_options[i])
	{
		ft_printf("%r `%s`: %s\n", fd,
			g_sh_options[i]->name,
			i18n_translate(g_sh_options[i]->index));
		i++;
	}
	return (EXIT_SUCCESS);
}

int		main(int argc, char *argv[], char *envp[])
{
	int	ret;
	t_sh	sh;

	(void)argc;
	logger_init(D_TRACE, "out.log");

	// shell options
	if ((sh.argv = ft_array_dup(argv)) == NULL)
		return (display_status(ST_MALLOC, NULL, NULL));
	if ((ret = option_parse(&sh.opt_head, g_sh_options, &sh.argv, 1)) != ST_OK)
		return (s_usage(ret));
	if (option_is_set(&sh.opt_head, ST_OPTION_HELP) == 1)
		return (s_usage(ST_OK));

	// why not place it in `shell_init()` ?
	environment_init(&sh, envp);

	if (option_is_set(&sh.opt_head, ST_OPTION_C) == 1)
		sh.is_interactive = 0;
	else
		sh.is_interactive = isatty(STDIN_FILENO);

	// we need to initialize the shell structure and co even if we are in `-c` mode
	if ((ret = shell_init(&sh)) != ST_OK)
		log_fatal("shell initialization failed (%d)", ret);

	if (option_is_set(&sh.opt_head, ST_OPTION_C) == 1)
		ret = parse(&sh, option_get_value(&sh.opt_head, ST_OPTION_C));
	else
	{
		if ((ret = stdin_loop(&sh)) != ST_END_OF_INPUT)
			log_fatal("get_next_line failed (%d)", ret);

		// temp ? arthur wants to move it in termcaps
		if (tcsetattr(0, TCSANOW, &sh.termios_old) == -1)
			log_fatal("tcsetattr() failed to restore the terminal");
		if (close(sh.fd) != 0)
			log_error("close() failed");
	}

	// shell_end()
	logger_close();
	return (sh.last_exit_status);
}

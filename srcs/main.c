#include "shell.h"

t_list	g_current_jobs_list_head = {
	.next = &g_current_jobs_list_head,
	.prev = &g_current_jobs_list_head
};

static void	usage(void)
{
	fprintf(stderr, "usage: ./42sh [opt]\n");
	fprintf(stderr, "	-h: display usage\n");
	fprintf(stderr, "	-c <command>\n");
}

int		main(int argc, char *argv[])
{
	int 	exit_status;
	int	ret;
	t_sh	sh;

	//TEMP ?
	enum {
		OPT_TYPE_UNDEFINED = 0,
		OPT_TYPE_COMMAND
	}	opt_type;

	int	c;
	char	*opt;

	while ((c = getopt(argc, argv, "hc:")) != -1)
	{
		switch (c)
		{
			case 'h':
				usage();
				return (0);
			case 'c':
				opt_type = OPT_TYPE_COMMAND;
				opt = optarg;
				log_debug("execute command %s", opt);
				break ;
			default:
				usage();
				return (1);
		}
	}
	if (optind != argc)
	{
		usage();
		return (1);
	}

	// shell_init()
	logger_init(D_TRACE, "out.log");
	INIT_LIST_HEAD(&g_current_jobs_list_head);

	exit_status = 0;
	sh.is_interactive = opt_type == OPT_TYPE_COMMAND ? false : isatty(STDIN_FILENO);
	if ((ret = shell_init(&sh)) != ST_OK)
		log_fatal("shell initialization failed (%d)", ret);
	if (opt_type == OPT_TYPE_COMMAND)
	{
		exit_status = parse(&sh, opt);
	}
	else
	{
		if ((exit_status = stdin_loop(&sh)) != ST_END_OF_INPUT)
			log_fatal("get_next_line failed (%d)", ret);
	}
	if (sh.is_interactive == true)
	{
		if (tcsetattr(0, TCSANOW, &sh.termios_old) == -1)
			log_fatal("tcsetattr() failed to restore the terminal");
		if (close(sh.fd) != 0)
			log_error("close() failed");
	}


	// shell_end()
	logger_close();
	return (exit_status);
}

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

int		main(int argc, char *argv[], char **envp)
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

//	(void)envp;
	environment_init(&sh, envp);
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
	if ((ret = shell_init(&sh)) != ST_OK)
		log_fatal("shell initialization failed (%d)", ret);
	INIT_LIST_HEAD(&g_current_jobs_list_head);

	exit_status = 0;
	if (opt_type == OPT_TYPE_COMMAND)
	{
		exit_status = parse(&sh, opt);
	}
	else
	{
		if (termcaps_init(&sh) != ST_OK)
		{
			 log_error("termcaps_init() failed");
			 return (-1);
		}
		// loop
		if ((exit_status = stdin_loop(&sh)) != ST_END_OF_INPUT)
			log_fatal("get_next_line failed (%d)", ret);
		if (!caps__finalize())
			return (-1); // Check le retour
		if (tcsetattr(0, TCSANOW, &sh.termios_old) == -1)
		  log_fatal("tcsetattr() failed to restore the terminal");
	}

	// shell_end()
	if (close(sh.fd) != 0)
		log_error("close() failed");
	logger_close();
	return (exit_status);
}

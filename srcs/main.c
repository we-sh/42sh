#include "shell.h"

t_job	*g_current_jobs = NULL;

int		main(int ac, const char *av[])
{
	(void)av;
	(void)ac;
	logger_init(D_TRACE, "out.log");
	shell_init();
	stdin_loop();
	logger_close();
	return (0);
}

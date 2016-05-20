#include "shell.h"

t_list	g_current_jobs_list_head = {
	.next = &g_current_jobs_list_head,
	.prev = &g_current_jobs_list_head
};

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

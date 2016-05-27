#include "shell.h"

t_list	g_current_jobs_list_head = {
	.next = &g_current_jobs_list_head,
	.prev = &g_current_jobs_list_head
};

int		main(int ac, const char *av[])
{
	int		ret;
	t_sh	sh;

	(void)av;
	(void)ac;
	logger_init(D_TRACE, "out.log");
	if ((ret = shell_init(&sh)) != ST_OK)
		log_fatal("shell initialization failed (%d)", ret);
	INIT_LIST_HEAD(&g_current_jobs_list_head);
	if ((ret = stdin_loop(&sh)) != ST_END_OF_INPUT)
		log_fatal("get_next_line failed (%d)", ret);
	if (!caps__finalize())
		return (-1); // Check le retour
	logger_close();
	return (0);
}

#include "shell.h"

t_list			*list_node__proc_alloc(char **argv)
{
	t_proc		*p;

	if ((p = malloc(sizeof(t_proc))) == NULL)
		return (NULL);
	p->argv = argv;
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	p->exit_status = EXIT_SUCCESS;
	p->builtin_status = ST_OK;
	return (&p->list_proc);
}

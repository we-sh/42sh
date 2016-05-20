#include "shell.h"

t_job	*job_alloc(char *command)
{
	t_job		*j;

	if ((j = malloc(sizeof(t_job))) == NULL)
		return (NULL);
	INIT_LIST_HEAD(&j->proc_head);
	j->command = command;
	j->foreground = 1;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	j->pgid = 0;
	j->notified = 0;
	return (j);
}

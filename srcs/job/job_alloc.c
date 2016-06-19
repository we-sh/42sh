#include "shell.h"

t_job	*job_alloc(char const *command)
{
	t_job		*j;

	if ((j = malloc(sizeof(t_job))) == NULL)
		return (NULL);
	INIT_LIST_HEAD(&j->proc_head);
	if ((j->command = ft_strdup(command)) == NULL)
		return (NULL);
	j->foreground = 1;
	j->launched = 0;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	j->stderr = STDERR_FILENO;
	j->pgid = 0;
	j->notified = 0;
	j->id = job_available_id();
	j->separator = F_JSEP_SEMI;
	j->exit_status = EXIT_SUCCESS;
	return (j);
}

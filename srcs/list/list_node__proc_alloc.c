#include "shell.h"

static int		s_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

t_list			*list_node__proc_alloc(char *command, char **argv, char **envp)
{
	t_proc		*p;

	if ((p = malloc(sizeof(t_proc))) == NULL)
		return (NULL);
	p->argv = argv;
	if ((p->command = ft_strdup(command)) == NULL)
		return (NULL);
	p->argc = s_argc(argv);
	if ((p->envp = ft_array_dup(envp)) == NULL)
		return (NULL);
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->signaled = 0;
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	p->exit_status = EXIT_SUCCESS;
	p->bltin_char = NULL;
	p->bltin_status = ST_OK;
	INIT_LIST_HEAD(&p->bltin_opt_head);
	return (&p->list_proc);
}

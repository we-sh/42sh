#include "shell.h"

/*
** Allocate a new processus with default values.
*/

static void		s_init_fds(t_proc *p)
{
	p->stdin = STDIN_FILENO;
	p->stdout = STDOUT_FILENO;
	p->stderr = STDERR_FILENO;
	p->pipe[0] = -1;
	p->pipe[1] = -1;
}

t_proc			*proc_alloc(t_sh *sh, t_job *j)
{
	t_proc		*p;

	if (!(p = ft_memalloc(sizeof(t_proc))))
		return (NULL);
	p->command = NULL;
	p->argv = NULL;
	p->j = j;
	if ((p->argv = (char **)malloc(sizeof(char *) * 1)) == NULL)
		return (NULL);
	p->argv[0] = NULL;
	p->envp = NULL;
	p->pid = 0;
	p->completed = 0;
	p->stopped = 0;
	p->signaled = 0;
	p->is_valid = 1;
	p->is_subshell = 0;
	p->exit_status = EXIT_SUCCESS;
	p->bltin_char = NULL;
	p->bltin_status = ST_OK;
	p->sh = sh;
	s_init_fds(p);
	INIT_LIST_HEAD(&p->bltin_opt_head);
	return (p);
}

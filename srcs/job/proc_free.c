#include "shell.h"

static void	s_close_non_standard_streams(t_proc *p)
{
	if (p->stdin != STDIN_FILENO && p->stdin != STDOUT_FILENO
		&& p->stdin != STDERR_FILENO)
	{
		log_info("closing non-standard stdin (%d)", p->stdin);
		close(p->stdin);
	}
	if (p->stdout != STDIN_FILENO && p->stdout != STDOUT_FILENO
		&& p->stdout != STDERR_FILENO)
	{
		log_info("closing non-standard stdout (%d)", p->stdout);
		close(p->stdout);
	}
	if (p->stderr != STDIN_FILENO && p->stderr != STDOUT_FILENO
		&& p->stderr != STDERR_FILENO)
	{
		log_info("closing non-standard stderr (%d)", p->stderr);
		close(p->stderr);
	}
}

void		proc_free(t_proc **p)
{
	t_option	*opt;
	t_list		*pos;
	t_list		*safe;
	t_list		*head;

	head = &(*p)->bltin_opt_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		opt = CONTAINER_OF(pos, t_option, list_option);
		option_free(&opt);
	}
	s_close_non_standard_streams(*p);
	ft_memdel_tab((void ***)&(*p)->argv);
	ft_memdel_tab((void ***)&(*p)->envp);
	ft_memdel((void **)&(*p)->command);
	ft_memdel((void **)&(*p)->bltin_char);
	ft_memdel((void **)&(*p));
	*p = NULL;
}

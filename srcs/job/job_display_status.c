#include "shell.h"

static void	s_proc_display_status(t_job *j, t_proc *p, char c, int show_pid)
{
	int		status;

	if (j->pgid == p->pid)
		ft_printf("[%d]\t%c ", j->id, c);
	else
		ft_putstr("   \t  ");
	if (show_pid > 0)
	{
		if (show_pid == 1 || (show_pid == 2 && j->pgid == p->pid))
			ft_printf("%d\t", p->pid);
		else
			ft_putstr(" \t");
	}
	status = ST_RUNNING;
	if (p->signaled != 0)
		status = ST_SIGNAL + p->signaled;
	else if (p->completed == 1)
		status = ST_DONE;
	else if (p->stopped == 1)
		status = ST_STOPPED;
	status =
	ft_printf("%-11s\t %s\n",
		i18n_translate(status),
		p->command);
}

int			job_display_status(t_job *j, int show_pid)
{
	t_list	*p_pos;
	t_proc	*p;
	char	c;

	c = ' ';
	if (job_background_nth(&g_current_jobs_list_head, -1) == j)
		c = '+';
	else if (job_background_nth(&g_current_jobs_list_head, -2) == j)
		c = '-';
	LIST_FOREACH(&j->proc_head, p_pos)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
		s_proc_display_status(j, p, c, show_pid);
	}
	return (ST_OK);
}

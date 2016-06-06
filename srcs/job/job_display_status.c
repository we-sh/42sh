#include "shell.h"

int	job_display_status(t_job *j, int show_pid)
{
	t_list	*p_pos;
	t_proc	*p;
	t_job	*j_tmp;
	char	c;
	int		status;

	c = ' ';

	if ((j_tmp = job_background_nth(&g_current_jobs_list_head, -1)) == j)
		c = '+';
	else if ((j_tmp = job_background_nth(&g_current_jobs_list_head, -2)) == j)
		c = '-';

	LIST_FOREACH(&j->proc_head, p_pos)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
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
			status = ST_TERMINATED;
		else if (p->completed == 1)
			status = ST_DONE;
		else if (p->stopped == 1)
			status = ST_STOPPED;
		status =
		ft_printf("%-11s %s\n",
			i18n_translate(status),
			p->command);
	}
	return (ST_OK);
}

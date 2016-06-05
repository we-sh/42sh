#include "shell.h"

static int	s_before(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		if (p->argc == 2)
			if (job_by_name(p->argv[1]) == NULL)
				p->bltin_status = ST_EINVAL;
	}
	return (ST_OK);
}

static int	s_display_proc_info(t_job *j, int show_pid)
{
	t_list	*p_pos;
	t_proc	*p;
	t_job	*j_tmp;
	char	c;

	c = ' ';

	// todo create a `list_nth_background_job` because we want to retrieve only background jobs from list
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
		ft_printf("%-10s %s\n",
			i18n_translate(p->completed == 1 ? ST_DONE : ST_RUNNING),
			p->command);
	}
	return (ST_OK);
}

static int	s_exec(t_proc *p)
{
	t_list	*j_pos;
	t_job	*j;
	int		show_pid;
	size_t	j_total;

	if (p->bltin_status != ST_OK)
	{
		// todo use `log_status()` instead
		ft_putendl_fd(i18n_translate(p->bltin_status), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	show_pid = option_is_set(&p->bltin_opt_head, ST_BLTIN_JOBS_OPT_L);
	if (show_pid == 0
		&& option_is_set(&p->bltin_opt_head, ST_BLTIN_JOBS_OPT_P) == 1)
		show_pid = 2;
	if (p->argc == 2)
	{
		if ((j = job_by_name(p->argv[1])) != NULL)
			s_display_proc_info(j, show_pid);
		return (EXIT_SUCCESS);
	}
	j_total = list_size(&g_current_jobs_list_head);
	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == 0)
			s_display_proc_info(j, show_pid);
	}
	return (EXIT_SUCCESS);
}

int			builtin_jobs(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	(void)builtin;
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(p));
	return (ST_OK);
}

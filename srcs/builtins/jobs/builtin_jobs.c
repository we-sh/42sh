#include "shell.h"

static int	s_before(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		// todo check jobs_id
	}
	return (ST_OK);
}

static int	s_display_proc_info(t_job *j, int show_pid, int position)
{
	t_list	*p_pos;
	t_proc	*p;

	LIST_FOREACH(&j->proc_head, p_pos)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
		if (j->pgid == p->pid)
		{
			ft_putstr("[");
			ft_putnbr(j->id);
			ft_putstr("] ");
			if (position == -1)
				ft_putstr("+ ");
			else if (position == -2)
				ft_putstr("- ");
			else
				ft_putstr("  ");
		}
		else
			ft_putstr("      ");
		if (show_pid == 1 || (show_pid == 2 && j->pgid == p->pid))
		{
			ft_putnbr(p->pid);
			ft_putstr(" ");
		}
		if (p->completed == 1)
			ft_putstr(i18n_translate(ST_DONE));
		else
			ft_putstr(i18n_translate(ST_RUNNING));
		ft_putstr(" ");
		ft_putendl(p->command);
	}
	return (ST_OK);
}

static int	s_exec(t_proc *p)
{
	t_list	*j_pos;
	t_job	*j;
	int		show_pid;
	size_t	j_total;
	int		position;

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
	j_total = list_size(&g_current_jobs_list_head);
	LIST_FOREACH(&g_current_jobs_list_head, j_pos)
	{
		position = 0;
		j = CONTAINER_OF(j_pos, t_job, list_job);
		//if (j->foreground == 0 || job_is_stopped(j) == 1)
		//{
			// todo display only background
			if (list_nth(&g_current_jobs_list_head, -1) == j_pos)
				position = -1;
			else if (list_nth(&g_current_jobs_list_head, -2) == j_pos)
				position = -2;
			s_display_proc_info(j, show_pid, position);
		//}
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

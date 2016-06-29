/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	s_before(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 2)
			p->bltin_status = ST_EINVAL;
		if (p->argc == 2)
			if (job_by_name(p->argv[1], 0) == NULL)
				p->bltin_status = ST_BLTIN_JOBS_ERR_NOSUCHJOB;
	}
	return (ST_OK);
}

static void	s_iterate_on_jobs(int show_pid)
{
	t_list	*j_pos;
	t_job	*j;
	size_t	j_total;

	j_total = list_size(&g_current_jobs_list_head);
	j_pos = &g_current_jobs_list_head;
	while ((j_pos = j_pos->next) && j_pos != &g_current_jobs_list_head)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == 0)
			job_display_status(j, show_pid);
	}
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	t_job	*j;
	int		show_pid;

	if (p->bltin_status > ST_OK)
	{
		if (p->bltin_status != ST_EINVAL && p->argc == 2)
			display_status(p->bltin_status, NULL, p->argv[1]);
		else
			builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	show_pid = option_is_set(&p->bltin_opt_head, ST_BLTIN_JOBS_OPT_L);
	if (show_pid == 0
		&& option_is_set(&p->bltin_opt_head, ST_BLTIN_JOBS_OPT_P) == 1)
		show_pid = 2;
	if (p->argc == 2)
	{
		if ((j = job_by_name(p->argv[1], 0)) != NULL)
			job_display_status(j, show_pid);
		return (EXIT_SUCCESS);
	}
	s_iterate_on_jobs(show_pid);
	return (EXIT_SUCCESS);
}

int			builtin_jobs(t_builtin const *builtin, int callback, t_sh *sh,
				t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	return (ST_OK);
}

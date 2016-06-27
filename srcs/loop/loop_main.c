#include "shell.h"

static int		s_is_launchable(t_job *j_prev)
{
	if (j_prev && j_prev->is_interrupted != 0)
		return (1 == 2);
	return (!j_prev || j_prev->separator == F_JSEP_SEMI
		|| (j_prev->separator == F_JSEP_AND_IF
			&& j_prev->exit_status == EXIT_SUCCESS)
		|| (j_prev->separator == F_JSEP_OR_IF
			&& j_prev->exit_status != EXIT_SUCCESS));
}

static int		s_process_job(t_sh *sh, t_job **j_prev, t_job *j)
{
	int			ret;

	if (s_is_launchable(*j_prev))
	{
		ret = parser(sh, j->command, F_PARSING_PROCS, &j->proc_head);
		if (ret != ST_OK)
			return (ret);
		if ((ret = job_launch(sh, j)) != ST_OK)
			return (ret);
	}
	else
	{
		j->exit_status = (*j_prev)->exit_status;
		j->notified = 1;
	}
	*j_prev = j;
	return (ST_OK);
}

static int		s_job_launcher(t_sh *sh, char *input)
{
	t_job		*j;
	t_job		*j_prev;
	t_list		*j_ptr;
	int			ret;

	ret = parser(sh, input, F_PARSING_JOBS, &g_current_jobs_list_head);
	if (ret != ST_OK)
		return (ret);
	j_prev = NULL;
	j_ptr = &g_current_jobs_list_head;
	while ((j_ptr = j_ptr->next) && j_ptr != &g_current_jobs_list_head)
	{
		j = CONTAINER_OF(j_ptr, t_job, list_job);
		if (j->launched == 0)
		{
			if ((ret = s_process_job(sh, &j_prev, j)) != ST_OK)
				return (ret);
		}
	}
	return (ST_OK);
}

int				loop_main(t_sh *sh)
{
	char		*input;
	int			ret;

	while (1)
	{
		ret = ST_OK;
		job_list_clean(1);
		input = NULL;
		if (sh->is_interactive == 1)
			input = termcaps_read_input(&sh->termcaps_context);
		else
			ret = get_next_line(sh->fd, &input);
		if (ret < 0 || (sh->is_interactive == 1 ? input == NULL : ret == 0))
			break ;
		if ((ret = parser(sh, input, F_PARSING_NONE, NULL)) == ST_OK)
		{
			if ((ret = s_job_launcher(sh, input)) != ST_OK)
				return (ret);
		}
		else
			sh->last_exit_status = EXIT_FAILURE;
		ft_strdel(&input);
	}
	return (ST_END_OF_INPUT);
}

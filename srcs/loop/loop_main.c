#include "shell.h"

static int				s_job_launcher(t_sh *sh)
{
	t_job		*j;
	t_job		*j_prev;
	t_list		*j_ptr;
	int			ret;

	j_prev = NULL;
	LIST_FOREACH(&g_current_jobs_list_head, j_ptr)
	{
		j = CONTAINER_OF(j_ptr, t_job, list_job);
		if (!j_prev || j_prev->separator == F_JSEP_SEMI
			|| (j_prev->separator == F_JSEP_AND_IF && j_prev->exit_status == EXIT_SUCCESS)
			|| (j_prev->separator == F_JSEP_OR_IF && j_prev->exit_status != EXIT_SUCCESS))
		{
			ret = job_launch(sh, j);
			if (ret != ST_OK)
				return (ret);
		}
		else
		{
			j->exit_status = j_prev->exit_status;
			j->notified = 1;
		}
		j_prev = j;
	}
	return (ST_OK);
}

int						loop_main(t_sh *sh)
{
	char				*input;
	int					ret;

	input = NULL;
	while (1)
	{
		job_list_clean(1);
		if (sh->is_interactive == 1)
			input = termcaps_read_input(&sh->termcaps_context);
		else
			ret = get_next_line(sh->fd, &input);
		if (sh->is_interactive == 1 ? input == NULL : ret == 0)
		{
			log_info("termcaps_read_input() returned NULL");
			break ;
		}
		// FIX
		if ((ret = parser(sh, input)) < 0)
			ret = 1;
		ft_strdel(&input);
		input = NULL;
		if (ret != ST_OK)
		{
			if (ret == ST_EXIT)
				return (ST_OK);
			display_status(ret, NULL, NULL);
		}
		else
		{
			if ((ret = s_job_launcher(sh)) != ST_OK)
			{
				return (ret);
			}
		}
	}
	return (ST_END_OF_INPUT);
}

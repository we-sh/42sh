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

static int		s_loop(t_sh *sh, char *input)
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

int				loop_job_launcher(t_sh *sh, char *input, int is_subshell)
{
	int			ret;

	if (is_subshell == 1)
	{
		char **tab;
		tab = ft_strsplit(input, '\n');
		int i = 0;
		while(tab[i])
		{
			log_debug("tab[i] '%s'", tab[i]);
			ret = parser(sh, tab[i], F_PARSING_NONE, NULL);
			if (ret != ST_OK && ret != ST_PARSER && ret != ST_LEXER)
			{
				log_debug("returned %d", ret);
				return (ret);
			}
			if (ret == ST_OK)
				if ((ret = s_loop(sh, tab[i])) != ST_OK)
					return (ret);
			i++;
		}
	} else
	{
		ret = parser(sh, input, F_PARSING_NONE, NULL);
		if (ret != ST_OK && ret != ST_PARSER && ret != ST_LEXER)
			return (ret);
		if (ret == ST_OK)
			if ((ret = s_loop(sh, input)) != ST_OK)
				return (ret);
	}
	return (ST_OK);
}

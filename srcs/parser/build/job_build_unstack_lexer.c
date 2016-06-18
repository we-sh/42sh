#include "parser.h"

/*
** For each token of the lexer, apply a function and build a 'job-tree' into the
** global variable g_current_jobs_list_head.
*/

int	job_build_unstack_lexer(t_lexer *lexer, char **envp)
{
	int		i;
	t_job	*j;

	if (!lexer || !envp)
		return (ST_EINVAL);
	i = 0;
	while (i < lexer->size)
	{
		if (!(j = job_build_unstack_job_from_lexer(lexer, &i, envp)))
			return (ST_PARSER);
		list_push_back(&j->list_job, &g_current_jobs_list_head);
	}

	log_success("parsing lexer into %zu jobs", list_size(&g_current_jobs_list_head));

	return (ST_OK);
}

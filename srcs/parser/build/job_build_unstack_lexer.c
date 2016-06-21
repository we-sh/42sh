#include "parser.h"

/*
** For each token of the lexer, apply a function and build a 'job-tree' into the
** global variable g_current_jobs_list_head.
*/

int	job_build_unstack_lexer(t_parser *parser)
{
	int		i;
	t_job	*j;
	int		ret;

	j = NULL;
	if (!parser)
		return (ST_EINVAL);
	i = 0;
	while (i < parser->lexer->size)
	{
		if ((ret = job_build_unstack_job_from_lexer(&j, parser->lexer, &i))
				!= ST_OK)
		{
			job_free(&j);
			return (ret);
		}
		list_push_back(&j->list_job, parser->target_list_head);
	}
	log_success("parsing lexer into %zu jobs",
			list_size(parser->target_list_head));
	return (ST_OK);
}

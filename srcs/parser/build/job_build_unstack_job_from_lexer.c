#include "parser.h"

/*
** Unstack the list of tokens to build a list of jobs.
*/

int	job_build_unstack_job_from_lexer(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	t_proc	*p;
	t_job	*j;

	if (!(j = job_alloc("")))
		return (ST_MALLOC);
	while (*i < lexer->size)
	{
		log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);
		if ((p = proc_alloc(j)) == NULL)
		{
			job_free(&j);
			return (ST_MALLOC);
		}
		if ((ret = job_build_unstack_proc_from_lexer(p, lexer, i)) != ST_OK)
		{
			proc_free(&p);
			job_free(&j);
			return (ret);
		}
		list_push_back(&p->list_proc, &j->proc_head);
		if (lexer->tokens[*i].type == TT_JOBS)
		{
			log_info("end of job encountered     ('%s')",
					lexer->tokens[*i].content);
			(*i)++;
			break ;
		}
		else if (lexer->tokens[*i].code == TC_PIPE)
		{
			log_info("end of process encountered ('%s')",
					lexer->tokens[*i].content);
			(*i)++;
		}
		else
			log_info("remaining tokens : %d / %d", lexer->size - *i,
					lexer->size);
	}
	list_push_back(&j->list_job, parser->target_list_head);
	return (ST_OK);
}

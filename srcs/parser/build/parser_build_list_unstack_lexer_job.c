#include "parser.h"

/*
** Unstack the list of tokens to build a list of jobs.
*/

int	parser_build_list_unstack_lexer_job(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	t_job	*j;

	while (*i < lexer->size)
	{
		log_info("remaining tokens (job) : %d / %d", lexer->size - *i, lexer->size);

		if (!(j = job_alloc("")))
			return (ST_MALLOC);

		while (*i < lexer->size && TOKEN_TYPE(*i) != TT_JOBS)
		{
			ret = lexer->tokens[*i]->parse((void *)j, parser, lexer, i);
			if (ret != ST_OK)
			{
				job_free(&j);
				return (ret);
			}
		}

		if (*i < lexer->size)
		{
			ret = lexer->tokens[*i]->parse((void *)j, parser, lexer, i);
			if (ret != ST_OK)
			{
				job_free(&j);
				return (ret);
			}
		}

		list_push_back(&j->list_job, parser->target_list_head);
	}
	return (ST_OK);
}

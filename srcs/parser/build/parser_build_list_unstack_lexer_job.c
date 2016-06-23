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

		while (*i < lexer->size && lexer->tokens[*i].type != TT_JOBS)
		{
			log_debug("%d %d", lexer->tokens[*i].type, lexer->tokens[*i].code);
			ret = lexer->tokens[*i].parse((void *)j, parser, lexer, i);
			if (ret != ST_OK)
			{
				job_free(&j);
				return (ret);
			}
		}

		if (*i < lexer->size)
		{
			ret = lexer->tokens[*i].parse((void *)j, parser, lexer, i);
			if (ret != ST_OK)
			{
				job_free(&j);
				return (ret);
			}
		}

		list_push_back(&j->list_job, parser->target_list_head);


		/*if ((p = proc_alloc(j)) == NULL)
		{
			job_free(&j);
			return (ST_MALLOC);
		}*/
		/*if ((ret = parser_build_list_unstack_lexer_proc(p, parser, lexer, i)) != ST_OK)
		{
			proc_free(&p);
			job_free(&j);
			return (ret);
		}*/

		//list_push_back(&p->list_proc, &j->proc_head);
		/*if (lexer->tokens[*i].type == TT_JOBS)
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
					*/
	}
	return (ST_OK);
}

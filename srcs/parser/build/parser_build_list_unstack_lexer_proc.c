#include "parser.h"

/*
** Unstack processus from the stack of tokens.
*/

int		parser_build_list_unstack_lexer_proc(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	t_proc	*p;
	t_job	*j;

	j = CONTAINER_OF(parser->target_list_head, t_job, proc_head);
	while (*i < lexer->size)
	{
		log_info("remaining tokens (proc) : %d / %d", lexer->size - *i, lexer->size);

		if (!(p = proc_alloc(j)))
			return (ST_MALLOC);

		while (*i < lexer->size
			&& !(TOKEN_TYPE(*i) == TT_REDIR && TOKEN_CODE(*i) == TC_PIPE))
		{

			ret = lexer->tokens[*i].parse((void *)p, parser, lexer, i);
			if (ret != ST_OK)
			{
				proc_free(&p);
				return (ret);
			}
		}

		if (*i < lexer->size)
		{
			ret = lexer->tokens[*i].parse((void *)p, parser, lexer, i);
			if (ret != ST_OK)
			{
				proc_free(&p);
				return (ret);
			}
		}

		list_push_back(&p->list_proc, parser->target_list_head);

	}
	return (ST_OK);
}

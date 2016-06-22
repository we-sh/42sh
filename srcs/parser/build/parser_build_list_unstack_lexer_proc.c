#include "parser.h"

/*
** Unstack processus from the stack of tokens.
*/

int		parser_build_list_unstack_lexer_proc(t_proc *p, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	while (*i < lexer->size)
	{
		ret = ST_OK;
		log_debug("unstacking token : %d / %d : \"%s\"", *i, lexer->size,
				lexer->tokens[*i].content);
		if (lexer->tokens[*i].code == TC_NONE && *i + 1 < lexer->size
				&& lexer->tokens[*i + 1].type == TT_REDIR)
			ret = lexer->tokens[(*i) + 1].parse((void *)p, parser, lexer, i);
		else
			ret = lexer->tokens[*i].parse(p, parser, lexer, i);
		if (lexer->tokens[*i].type == TT_JOBS
				|| lexer->tokens[*i].code == TC_PIPE)
			break ;
		if (ret != ST_OK)
		{
			log_error("error on token parsing");
			return (ret);
		}
		(*i)++;
	}
	return (ret);
}

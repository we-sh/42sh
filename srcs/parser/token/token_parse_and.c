#include "parser.h"

int	token_parse_and(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&'", "TT_SPECIAL");

	if (*i < lexer->size)
	{
		if (lexer->tokens[(*i) + 1].code == TC_CHEV_RIGHT)
			return (token_parse_chev_right(p, lexer, i));
		else
			return (token_parse_none(p, lexer, i));
	}
	return (ST_OK);
}

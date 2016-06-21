#include "parser.h"

int	token_parse_and(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&'", "TT_SPECIAL");

	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "&");
		return (ST_PARSER);
	}
	if (*i < lexer->size)
	{
		if (lexer->tokens[(*i) + 1].code == TC_CHEV_RIGHT)
			return (token_parse_chev_right(p, lexer, i));
		else if (lexer->tokens[(*i) + 1].code == TC_DBL_CHEV_RIGHT)
		{
			display_status(ST_PARSER_TOKEN, NULL, "&");
			return (ST_PARSER);
		}
		else
		{
			p->j->foreground = 0;
			return (token_parse_none(p, lexer, i));
		}
	}
	return (ST_OK);
}

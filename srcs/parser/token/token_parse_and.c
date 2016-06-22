#include "parser.h"

int	token_parse_and(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&'", "TT_SPECIAL");

	// todo: use parsing mode to customize what this function does
	t_proc	*p;
	p = (t_proc *)target;
	(void)parser;

	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "&");
		return (ST_PARSER);
	}
	if (*i < lexer->size)
	{
		if (lexer->tokens[(*i) + 1].code == TC_CHEV_RIGHT)
			return (token_parse_chev_right(target, parser, lexer, i));
		else if (lexer->tokens[(*i) + 1].code == TC_DBL_CHEV_RIGHT)
		{
			display_status(ST_PARSER_TOKEN, NULL, "&");
			return (ST_PARSER);
		}
		else
		{
			p->j->foreground = 0;
			return (token_parse_none(target, parser, lexer, i));
		}
	}
	return (ST_OK);
}

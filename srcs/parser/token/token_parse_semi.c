#include "parser.h"

int	token_parse_semi(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s ';'", "TT_JOBS");
	(void)lexer;
	(void)i;

	// todo: use parsing mode to customize what this function does
	t_proc	*p;
	p = (t_proc *)target;
	(void)parser;

	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, ";");
		return (ST_PARSER);
	}
	return (ST_OK);
}

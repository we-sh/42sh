#include "parser.h"

int	token_parse_dbl_or(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '||'", "TT_JOBS");

	// todo: use parsing mode to customize what this function does
	t_proc	*p;
	p = (t_proc *)target;
	(void)parser;

	(void)lexer;
	(void)i;
	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "||");
		return (ST_PARSER);
	}
	p->j->separator = F_JSEP_OR_IF;
	return (0);
}

#include "shell.h"

int			token_globing_parse_inhib(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	log_trace("  entering parsing token %-12s", "TT_INHIBITOR");

	(void)parser;
	(void)lexer;
	(void)target;
	(*i)++;
	return (ST_OK);
}

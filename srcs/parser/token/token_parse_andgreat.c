#include "parser.h"

/*
** Operator: &>
** Type:     TT_REDIR
** Code:     TC_ANDGREAT
*/

int	token_parse_andgreat(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&>'", "TT_REDIR");

	(void)lexer;
	(void)i;
	(void)parser;
	(void)target;

	return (ST_OK);
}

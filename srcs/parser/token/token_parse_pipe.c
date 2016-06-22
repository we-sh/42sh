#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_pipe(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '|'", "TT_REDIR");
	(void)lexer;
	(void)i;

	// todo: use parsing mode to customize what this function does
	t_proc	*p;
	p = (t_proc *)target;
	(void)parser;

	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "|");
		return (ST_PARSER);
	}
	return (0);
}

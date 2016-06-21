#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_pipe(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '|'", "TT_REDIR");
	(void)lexer;
	(void)i;
	if (p->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "|");
		return (ST_PARSER);
	}
	return (0);
}

#include "parser.h"

int	token_parse_semi(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s ';'", "TT_JOBS");
	(void)lexer;
	(void)i;
	(void)proc;
	if (proc->argc == 0)
	{
		display_status(ST_PARSER, NULL, "unexpected token near ';'");
		return (ST_PARSER);
	}
	return (ST_OK);
}

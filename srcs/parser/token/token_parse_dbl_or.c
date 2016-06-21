#include "parser.h"

int	token_parse_dbl_or(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '||'", "TT_JOBS");
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

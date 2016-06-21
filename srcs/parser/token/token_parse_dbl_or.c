#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_dbl_or(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '||'", "TT_JOBS");
	(void)lexer;
	(void)i;
	if (proc->argc == 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, "||");
		return (ST_PARSER);
	}
	proc->j->separator = F_JSEP_OR_IF;
	return (0);
}

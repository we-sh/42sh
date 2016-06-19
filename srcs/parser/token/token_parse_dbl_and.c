#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_dbl_and(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&&'", "TT_JOBS");
	(void)lexer;
	(void)i;
	proc->j->separator = F_JSEP_AND_IF;
//	job->wait = F_WAIT_SUCCESS;
//	(void)token;
	return (0);
}

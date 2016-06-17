#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_dbl_and(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '&&'", "TT_JOBS");
	(void)proc;
	(void)lexer;
	(void)i;
//	job->wait = F_WAIT_SUCCESS;
//	(void)token;
	return (0);
}

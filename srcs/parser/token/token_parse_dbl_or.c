#include "parser.h"

/*
** Return -1 on error, 0 on success, or 1 if a job delimiter is find.
*/
int	token_parse_dbl_or(t_node_job *job, char *token)
{
	log_trace("entering token parsing of ||");
	job->wait = F_WAIT_ERROR;
	(void)token;
	return (1);
}

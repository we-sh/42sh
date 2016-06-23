#include "parser.h"

static int	s_job(t_job *j)
{
	j->separator = F_JSEP_OR_IF;
	return (ST_OK);
}

int			token_parse_or_if(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '||'", "TT_JOBS");

	int		ret;

	(void)lexer;
	ret = ST_OK;
	if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target);
	(*i)++;
	return (0);
}

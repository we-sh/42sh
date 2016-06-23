#include "parser.h"

static int	s_job(t_job *j)
{
	j->separator = F_JSEP_SEMI;
	return (ST_OK);
}

int			token_parse_semi(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s ';'", "TT_JOBS");

	int		ret;

	(void)parser;
	(void)lexer;
	ret = ST_OK;
	if (parser->mode != F_PARSING_JOBS)
		ret = s_job((t_job *)target);
	(*i)++;
	return (ST_OK);
}

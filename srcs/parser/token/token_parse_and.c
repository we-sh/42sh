#include "parser.h"

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	j->foreground = 0;
	return (ST_OK);
}

int			token_parse_and(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	ret = ST_OK;
	if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	(*i)++;
	return (ST_OK);
}

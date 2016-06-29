#include "parser.h"

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	int		ret;

	ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command);
	if (ret != ST_OK)
		return (ret);
	return (ST_OK);
}

int			token_parse_inhib(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	(void)parser;
	ret = ST_OK;
	if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	(*i)++;
	return (ret);
}

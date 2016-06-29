#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	int		k;

	k = *i - 1;
	while (k >= 0 && TOKEN_TYPE(k) == TT_SEPARATOR)
		k--;
	if (k < 0)
	{
		display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	if (*i + 1 < lexer->size && TOKEN_CODE(*i + 1) == TC_AND)
	{
		display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i + 1));
		return (ST_PARSER);
	}
	return (ST_OK);
}

static int	s_jobs(t_job *j)
{
	j->separator = F_JSEP_AND_IF;
	return (ST_OK);
}

int			token_parse_and_if(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target);
	(*i)++;
	return (ret);
}

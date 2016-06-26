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
	return (ST_OK);
}

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
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target);
	(*i)++;
	return (ret);
}

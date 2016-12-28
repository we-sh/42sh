#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	int		k;

	k = *i - 1;
	while (k >= 0 && TOKEN_TYPE(k) == TT_SEPARATOR)
		k--;
	if (k < 0 || TOKEN_TYPE(k) == TT_JOBS || TOKEN_CODE(k) == TC_LPAREN)
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	if (*i + 1 < lexer->size && TOKEN_TYPE(*i + 1) == TT_JOBS)
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	return (ST_OK);
}

static int	s_job(t_job *j)
{
	j->separator = F_JSEP_SEMI;
	return (ST_OK);
}

int			token_parse_semi(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	(void)parser;
	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_job((t_job *)target);
	(*i)++;
	return (ret);
}

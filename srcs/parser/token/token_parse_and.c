#include "parser.h"

static int	s_none(t_lexer *lexer, int *i)
{
	int		k;

	k = *i + 1;
	while (k < lexer->size)
	{
		if (TOKEN_TYPE(k) != TT_SEPARATOR && TOKEN_TYPE(k) != TT_NAME
			&& !(TOKEN_TYPE(k) == TT_JOBS && TOKEN_CODE(k) == TC_SEMI))
		{
			if (lexer->notify == 1)
				display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(k));
			return (ST_PARSER);
		}
		k++;
	}
	k = *i - 1;
	while (k >= 0 && TOKEN_TYPE(k) == TT_SEPARATOR)
		k--;
	if (k == -1 || (TOKEN_TYPE(k) != TT_NAME && TOKEN_CODE(k) != TC_RPAREN))
	{
		if (lexer->notify == 1)
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	return (ST_OK);
}

static int	s_jobs(t_job *j, t_lexer *lexer, int *i)
{
	if (token_parse_utils_push_command(TOKEN_CONTENT(*i), &j->command) != ST_OK)
		return (ST_MALLOC);
	j->foreground = 0;
	return (ST_OK);
}

int			token_parse_and(void *target, t_parser *parser, t_lexer *lexer,
				int *i)
{
	int		ret;

	ret = ST_OK;
	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);
	else if (parser->mode == F_PARSING_JOBS)
		ret = s_jobs((t_job *)target, lexer, i);
	(*i)++;
	return (ret);
}

#include "shell.h"

static int	s_none(t_lexer *lexer, int *i)
{
	char	*content;

	if (TOKEN_CODE(*i) != TC_GREATAND)
		(*i)++;
	content = TOKEN_CONTENT(*i);
	(*i)++;
	token_parse_utils_skip_separators(lexer, i, NULL);
	if (*i < lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		display_status(ST_PARSER_TOKEN, NULL, content);
		return (ST_PARSER);
	}
	return (ST_OK);
}

int			token_parse_greatand(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	(void)target;
	(void)lexer;
	(void)parser;

	lexer->tokens[*i].is_redir_checked = 1;
	ret = ST_OK;

	if (parser->mode == F_PARSING_NONE)
		ret = s_none(lexer, i);

	(*i)++;
	return (ST_OK);
}

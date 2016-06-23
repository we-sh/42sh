#include "shell.h"

int			token_parse_utils_get_full_word(char **content, t_lexer *lexer,
				int *i)
{
	char	*tmp;

	while (*i < lexer->size && TOKEN_TYPE(*i) == TT_INHIBITOR)
		(*i)++;
	if (*i >= lexer->size || TOKEN_TYPE(*i) != TT_NAME)
	{
		if (*i < lexer->size)
			display_status(ST_PARSER_TOKEN, NULL, TOKEN_CONTENT(*i));
		return (ST_PARSER);
	}
	if ((*content = ft_strdup(TOKEN_CONTENT(*i))) == NULL)
		return (ST_MALLOC);
	(*i)++;
	while (*i < lexer->size && (TOKEN_TYPE(*i) == TT_INHIBITOR
									|| TOKEN_TYPE(*i) == TT_NAME))
	{
		if (TOKEN_TYPE(*i) == TT_NAME)
		{
			tmp = ft_strjoin(*content, TOKEN_CONTENT(*i));
			free(*content);
			*content = tmp;
		}
		(*i)++;
	}
	return (ST_OK);
}

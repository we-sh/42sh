#include "shell.h"

int			token_parse_utils_get_full_word(char **content, t_lexer *lexer,
				int *i)
{
	char	*tmp;

	if (lexer->tokens[*i].type != TT_NAME)
	{
		if ((*i) - 1 >= 0)
			display_status(ST_PARSER_TOKEN, NULL, lexer->tokens[(*i)].content);
		return (ST_PARSER);
	}
	if ((*content = ft_strdup(lexer->tokens[*i].content)) == NULL)
		return (ST_MALLOC);
	while (lexer->tokens[*i + 1].type == TT_INHIBITOR
		|| lexer->tokens[*i + 1].type == TT_NAME)
	{
		if (lexer->tokens[*i + 1].type == TT_NAME
			&& lexer->tokens[*i + 1].code == TC_NONE)
		{
			tmp = ft_strjoin(*content, lexer->tokens[*i + 1].content);
			free(*content);
			*content = tmp;
		}
		(*i)++;
	}
	return (ST_OK);
}

#include "shell.h"

int			token_parse_utils_get_word_and_inhib(char **content, t_lexer *lexer,
				int *i)
{
	char	*tmp;

	if ((*content = ft_strdup("")) == NULL)
		return (ST_MALLOC);
	while (*i < lexer->size && (TOKEN_TYPE(*i) == TT_INHIBITOR
								|| TOKEN_TYPE(*i) == TT_NAME))
	{
		if ((tmp = ft_strjoin(*content, TOKEN_CONTENT(*i))) == NULL)
			return (ST_MALLOC);
		free(*content);
		*content = tmp;
		(*i)++;
	}
	return (ST_OK);
}

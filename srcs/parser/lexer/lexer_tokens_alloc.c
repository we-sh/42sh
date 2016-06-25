#include "shell.h"

int			lexer_tokens_alloc(t_lexer *lexer)
{
	int		i;

	i = sizeof(t_token *) * (TOKEN_LIST_REALLOC);
	if ((lexer->tokens = (t_token **)malloc(i)) == NULL)
		return (ST_MALLOC);
	i = 0;
	while (i < TOKEN_LIST_REALLOC)
	{
		lexer->tokens[i] = NULL;
		i++;
	}
	lexer->allocated_size = TOKEN_LIST_REALLOC;
	lexer->size = 0;
	return (ST_OK);
}

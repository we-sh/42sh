#include "shell.h"

int		lexer_token_add(t_lexer *lexer, const char *str, t_token token)
{
	t_token		*item;

	if ((item = (t_token *)malloc(sizeof(t_token))) == NULL)
		return (ST_MALLOC);
	if ((item->content = ft_strdup(str)) == NULL)
		return (ST_MALLOC);
	item->len = token.len;
	item->is_redir_checked = 0;
	item->type = token.type;
	item->code = token.code;
	item->parse = token.parse;
	if (lexer_tokens_realloc(lexer) != ST_OK)
		return (ST_MALLOC);
	lexer->tokens[lexer->size] = item;
	lexer->size++;
	return (ST_OK);
}

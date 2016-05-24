#include "shell.h"

static void s_lexer_add(t_lexer *lexer, const char *str,
	size_t len, t_token_type type, t_token_code code)
{
	t_lexer_token item;
	ft_strncpy(item.content, str, len);
	item.content[len] = '\0';
	item.len = len;
	item.type = type;
	item.code = code;
	lexer->tokens[lexer->size] = item;
	(lexer->size)++;
}

static t_token *s_token_recognizer(const char *s)
{
	const t_token *list = token_list();

	while (list && list->op)
	{
		if (ft_strncmp(s, list->op, list->len) == 0)
			return ((t_token *)list);
		list++;
	}
	return NULL;
}

int		tokenize(const char *s, t_lexer *lexer)
{
	char		buf[TOKEN_BUF_SIZE];
	int			i;
	int			j;
	t_token		*token_found;

	ft_bzero(buf, TOKEN_BUF_SIZE);
	i = 0;
	j = 0;
	while (s && s[i])
	{
		token_found = s_token_recognizer(&s[i]);

		if (token_found != NULL)
		{
			/* add TOKEN_NAME if exists and reset buffer */
			if (ft_strlen(buf) > 0)
			{
				s_lexer_add(lexer, buf, ft_strlen(buf), TT_NAME, TC_NONE);
				ft_bzero(buf, TOKEN_BUF_SIZE);
				j = 0;
			}
			s_lexer_add(lexer, &s[i], token_found->len, token_found->type, token_found->code);
			i += token_found->len;
		}
		else
		{
			buf[j] = s[i];
			j++;
			i++;
		}
	}
	if (ft_strlen(buf) > 0)
		s_lexer_add(lexer, buf, ft_strlen(buf), TT_NAME, TC_NONE);
	return (ST_OK);
}

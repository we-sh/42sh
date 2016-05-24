#include "shell.h"

static void		s_lexer_add(t_lexer *lexer, const char *str, t_token token)
{
	t_lexer_token item;

	ft_strncpy(item.content, str, token.len);
	item.content[token.len] = '\0';
	item.len = token.len;
	item.type = token.type;
	item.code = token.code;
	lexer->tokens[lexer->size] = item;
	(lexer->size)++;
}

static t_token	*s_token_recognizer(const char *s)
{
	const t_token *list = token_list();

	while (list && list->op)
	{
		if (ft_strncmp(s, list->op, list->len) == 0)
			return ((t_token *)list);
		list++;
	}
	return (NULL);
}

static char		g_buf[TOKEN_BUF_SIZE];
static int		g_buf_index;

/*
** Fill buffer char by char in order to catch TT_NAME.
*/

static void		s_bufferize(char c)
{
	g_buf[g_buf_index] = c;
	g_buf_index++;
	/* TODO: handle this case correctly */
	if (g_buf_index >= TOKEN_BUF_SIZE)
	{
		log_error("Buffer overflow.\n");
		exit(ST_BUFFER);
	}
}

/*
** Add buffer to lexer as TT_NAME and reset buffer.
*/

static void		s_buffer_dump(t_lexer *lexer)
{
	t_token t;

	if (g_buf_index > 0)
	{
		g_buf[g_buf_index] = '\0';
		t.len = g_buf_index;
		t.type = TT_NAME;
		t.code = TC_NONE;
		s_lexer_add(lexer, g_buf, t);
		ft_bzero(g_buf, TOKEN_BUF_SIZE);
		g_buf_index = 0;
	}
}

int				tokenize(const char *s, t_lexer *lexer)
{
	t_token	*token_found;
	int		i;

	i = 0;
	while (s && s[i])
	{
		token_found = s_token_recognizer(&s[i]);
		if (token_found != NULL)
		{
			s_buffer_dump(lexer);
			s_lexer_add(lexer, &s[i], *token_found);
			i += token_found->len;
		}
		else
			s_bufferize(s[i++]);
	}
	s_buffer_dump(lexer);
	return (ST_OK);
}

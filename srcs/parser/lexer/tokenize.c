#include "shell.h"

/*
** Simple implementation of lexer
** Just return array of tokens
** Support some inhibitors like quotes and double quotes
*/

static void		s_lexer_add(t_lexer *lexer, const char *str, t_token token)
{
	t_lexer_token item;

	ft_strncpy(item.content, str, token.len);
	item.content[token.len] = '\0';
	item.len = token.len;
	item.is_redir_checked = 0;
	item.type = token.type;
	item.code = token.code;
	item.parse = token.parse;
	lexer->tokens[lexer->size] = item;
	(lexer->size)++;
}

static t_token	*s_token_recognizer(t_parser *parser, const char *s, int i)
{
	int			is_escaped;
	int			k;
	int			l;

	if (i > 0)
	{
		k = 0;
		is_escaped = 0;
		while (i - k > 0)
		{
			k++;
			if (*(s - k) != '\\')
				break;
			is_escaped = is_escaped == 1 ? 0 : 1;
		}
		if (is_escaped == 1)
			return (NULL);
	}
	l = 0;
	while (parser->token_list[l])
	{
		if (ft_strncmp(s, parser->token_list[l]->op, parser->token_list[l]->len) == 0)
		{
			return ((t_token *)parser->token_list[l]);
		}
		l++;
	}
	return (NULL);
}

static char		g_buf[TOKEN_BUF_SIZE];
static int		g_buf_index;

/*
** Fill buffer char by char in order to catch TT_NAME.
** TODO: add strncat function to libft (WHAAAAAAAAAAATT CEST PAS DEDANS???)
** TODO: handle this case correctly
*/

static void		s_bufferize(const char *str, size_t len)
{
	if (g_buf_index + len >= TOKEN_BUF_SIZE - 1)
	{
		log_error("buffer overflow.\n");
		exit(ST_BUFFER);
	}
	strncat(g_buf, str, len);
	g_buf_index += len;
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
		t.parse = token_parse_none;
		s_lexer_add(lexer, g_buf, t);
		ft_bzero(g_buf, TOKEN_BUF_SIZE);
		g_buf_index = 0;
	}
}

/*
** Will returns true the next call otherwise token inhib himself.
*/

static int		g_inhibitor_code;

int				s_inhibited_code(t_token *token)
{
	if (token != NULL && token->type == TT_INHIBITOR)
	{
		if (token->code == g_inhibitor_code)
			g_inhibitor_code = 0;
		else if (g_inhibitor_code == 0)
		{
			g_inhibitor_code = token->code;
			return (0);
		}
	}
	return (g_inhibitor_code);
}

/*
** Parse string argument chars by chars in order to detect special shell
** operators If no operators are detected, current char will be bufferized
*/

int				tokenize(const char *s, t_parser *parser)
{
	t_token	*token_found;
	int		is_inhibited;
	int		i;
	int 	ret;

	i = 0;
	is_inhibited = 0;
	g_inhibitor_code = 0;
	while (s && s[i])
	{
		token_found = s_token_recognizer(parser, s + i, i);
		is_inhibited = s_inhibited_code(token_found);
		if (token_found != NULL && is_inhibited != 0)
		{
			s_bufferize(token_found->op, token_found->len);
			i += token_found->len;
		}
		else if (token_found != NULL && is_inhibited == 0)
		{
			s_buffer_dump(parser->lexer);
			s_lexer_add(parser->lexer, &s[i], *token_found);
			i += token_found->len;
		}
		else
			s_bufferize(&s[i++], 1);
	}
	s_buffer_dump(parser->lexer);
	ret = s_inhibited_code(NULL);
	if (parser->mode == F_PARSING_TERMCAPS)
	{
		if (ret == 0 && token_found)
			ret = token_found->code == TC_BACKSLASH ? TC_BACKSLASH : 0;
	}
	else
		ret = ret != 0 ? ST_LEXER : ST_OK;
	return (ret);
}

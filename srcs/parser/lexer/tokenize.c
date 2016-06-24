#include "shell.h"

/*
** Simple implementation of lexer
** Just return array of tokens
** Support some inhibitors like quotes and double quotes
*/

static void		s_free_tokens(t_lexer *lexer)
{
	int			i;

	i = 0;
	while (i < lexer->size)
	{
		log_trace("freeing index: %d", i);
		free(lexer->tokens[i]->content);
		free(lexer->tokens[i]);
		i++;
	}
	free(lexer->tokens);
}

static int		s_realloc_tokens(t_lexer *lexer)
{
	t_token		**new_token_list;
	int			i;

	log_error("lexer->size: %d, lexer->size_allocated: %d", lexer->size, lexer->size_allocated);
	if (lexer->size + 1 >= lexer->size_allocated)
	{
		lexer->size_allocated += TOKEN_LIST_REALLOC;
		if ((new_token_list = (t_token **)malloc(sizeof(t_token *) * (lexer->size_allocated + 1))) == NULL)
			return (ST_MALLOC);
		i = 0;
		while (i < lexer->size)
		{
			log_error("copy index: %d (content: `%s')", i, lexer->tokens[i]->content);
			new_token_list[i] = lexer->tokens[i];
			i++;
		}
		while (i < lexer->size_allocated)
		{
			log_error("set to null index: %d", i);
			new_token_list[i] = NULL;
			i++;
		}
		s_free_tokens(lexer);
		lexer->tokens = new_token_list;
	}
	return (ST_OK);
}

static int		s_lexer_add(t_lexer *lexer, const char *str, t_token token)
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
	if (s_realloc_tokens(lexer) != ST_OK)
		return (ST_MALLOC);
	log_error("add index: %d (content: `%s')", lexer->size, item->content);
	lexer->tokens[lexer->size] = item;
	lexer->size++;
	return (ST_OK);
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

static char		*g_buf;
static int		g_buf_size_allocated;
static int		g_buf_index;

/*
** Fill buffer char by char in order to catch TT_NAME.
** TODO: add strncat function to libft (WHAAAAAAAAAAATT CEST PAS DEDANS???)
** TODO: handle this case correctly
*/

static int		s_bufferize(const char *str, int len)
{
	char		*tmp;

	if (g_buf_index + len >= g_buf_size_allocated)
	{
		tmp = g_buf;
		if ((g_buf = ft_strnew(g_buf_index + len + TOKEN_BUFFER_REALLOC)) == NULL)
			return (ST_MALLOC);
		g_buf = ft_strcpy(g_buf, tmp);
		free(tmp);
	}
	ft_strncat(g_buf, str, len);
	g_buf_index += len;
	return (ST_OK);
}

/*
** Add buffer to lexer as TT_NAME and reset buffer.
*/

static int		s_buffer_dump(t_parser *parser, t_lexer *lexer)
{
	t_token 	t;

	if (g_buf_index > 0)
	{
		g_buf[g_buf_index] = '\0';
		t.len = g_buf_index;
		t.type = TT_NAME;
		t.code = TC_NONE;
		if (parser->mode == F_PARSING_GLOBING)
			t.parse = token_globing_parse_none;
		else
			t.parse = token_parse_none;
		if (s_lexer_add(lexer, g_buf, t) != ST_OK)
		 	return (ST_MALLOC);
		ft_bzero(g_buf, g_buf_size_allocated);
		g_buf_index = 0;
	}
	return (ST_OK);
}

/*
** Will returns true the next call otherwise token inhib himself.
*/

static int		g_inhibitor_code;
static int		g_parenthesis_code;

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

static int		s_parenthesis_code(t_token *token)
{
	if (token != NULL && g_inhibitor_code == 0
		&& (token->code == TC_LBRACE || token->code == TC_RBRACE))
	{
		if (g_parenthesis_code == 0)
		{
			if (token->code == TC_LBRACE)
				g_parenthesis_code = 1;
		}
		else if (g_parenthesis_code == TC_LBRACE)
		{
			if (token->code == TC_RBRACE)
				g_parenthesis_code = 0;
		}
	}
	return (g_parenthesis_code);
}

/*
** Parse string argument chars by chars in order to detect special shell
** operators If no operators are detected, current char will be bufferized
*/

int				tokenize(const char *s, t_parser *parser)
{
	t_token	*token_found;
	int		is_inhibited;
	int		is_parenthesized;
	int		i;
	int 	ret;

	if ((g_buf = ft_strnew(TOKEN_BUFFER_REALLOC)) == NULL)
		return (ST_MALLOC);
	g_buf_size_allocated = TOKEN_BUFFER_REALLOC;

	i = 0;
	is_inhibited = 0;
	is_parenthesized = 0;
	g_inhibitor_code = 0;
	g_parenthesis_code = 0;
	while (s && s[i])
	{
		token_found = s_token_recognizer(parser, s + i, i);
		is_inhibited = s_inhibited_code(token_found);
		is_parenthesized = s_parenthesis_code(token_found);
		if (token_found != NULL && is_inhibited != 0)
		{
			if (s_bufferize(token_found->op, token_found->len) != ST_OK)
				return (ST_MALLOC);
			i += token_found->len;
		}
		else if (token_found != NULL && is_inhibited == 0)
		{
			if ((ret = s_buffer_dump(parser, parser->lexer)) != ST_OK)
				return (ret);
			if ((ret = s_lexer_add(parser->lexer, token_found->op, *token_found)) != ST_OK)
				return (ret);
			i += token_found->len;
		}
		else if (s_bufferize(&s[i++], 1) != ST_OK)
			return (ST_MALLOC);
	}
	if ((ret = s_buffer_dump(parser, parser->lexer)) != ST_OK)
		return (ret);
	is_parenthesized = s_parenthesis_code(token_found);
	ret = s_inhibited_code(NULL);
	if (parser->mode == F_PARSING_TERMCAPS)
	{
		if (ret == 0 && token_found)
		{
			// todo: skip for separators here !!!
			int	index;
			index = parser->lexer->size;
			while (index >= 0 && parser->lexer->tokens[index]->type == TT_SEPARATOR)
				index--;

			token_found = parser->lexer->tokens[index];
			if ((parser->lexer->size == 1 && token_found->code == TC_LBRACE)
				|| token_found->code == TC_PIPE
				|| token_found->code == TC_AND_IF
				|| token_found->code == TC_OR_IF)
				ret = token_found->code;
			else
				ret = token_found->code == TC_BACKSLASH ? TC_BACKSLASH : 0;
		}
		log_success("lexer termcaps results in: %d", ret);
	}
	else
		ret = ret != 0 ? ST_LEXER : ST_OK;
	return (ret);
}

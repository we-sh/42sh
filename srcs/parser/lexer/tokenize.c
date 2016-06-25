#include "shell.h"

/*
** Simple implementation of lexer
** Just return array of tokens
** Support some inhibitors like quotes and double quotes
*/

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
				g_parenthesis_code = TC_LBRACE;
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

int				tokenize(const char *s, t_parser *parser, t_lexer *lexer)
{
	t_token	*token_found;
	int		is_inhibited;
	int		is_parenthesized;
	int		i;
	int 	ret;

	i = 0;
	is_inhibited = 0;
	is_parenthesized = 0;
	g_inhibitor_code = 0;
	g_parenthesis_code = 0;
	while (s && s[i])
	{
		token_found = token_recognizer(parser, s + i, i);
		is_inhibited = s_inhibited_code(token_found);
		is_parenthesized = s_parenthesis_code(token_found);
		if (token_found != NULL && is_inhibited != 0)
		{
			if (lexer_bufferize(lexer, token_found->op, token_found->len) != ST_OK)
				return (ST_MALLOC);
			i += token_found->len;
		}
		else if (token_found != NULL && is_inhibited == 0)
		{
			if ((ret = lexer_buffer_dump(parser, lexer)) != ST_OK)
				return (ret);
			if ((ret = lexer_token_add(lexer, token_found->op, *token_found)) != ST_OK)
				return (ret);
			i += token_found->len;
		}
		else if (lexer_bufferize(lexer, &s[i++], 1) != ST_OK)
			return (ST_MALLOC);
	}
	if ((ret = lexer_buffer_dump(parser, lexer)) != ST_OK)
		return (ret);
	is_parenthesized = s_parenthesis_code(token_found);
	ret = s_inhibited_code(NULL);
	if (parser->mode == F_PARSING_TERMCAPS)
	{
		if (ret == 0 && token_found)
		{
			if (g_parenthesis_code != 0)
				return (g_parenthesis_code);
			// todo: skip for separators here !!!
			int	index;
			index = parser->lexer->size;
			while (index > 0 && parser->lexer->tokens[index]->type == TT_SEPARATOR)
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

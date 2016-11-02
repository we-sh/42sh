#include "shell.h"

/*
** Simple implementation of lexer
** Just return array of tokens
** Support some inhibitors like quotes and double quotes
*/

/*
** Will returns true the next call otherwise token inhib himself.
*/

int				s_inhibited_code(t_lexer *lexer, t_token *token)
{
	if (token != NULL && token->type == TT_INHIBITOR)
	{
		if (token->code == lexer->is_inhibited)
			lexer->is_inhibited = 0;
		else if (lexer->is_inhibited == 0)
		{
			lexer->is_inhibited = token->code;
			return (0);
		}
	}
	return (lexer->is_inhibited);
}

static int		s_parenthesis_code(t_lexer *lexer, t_token *token)
{
	if (token != NULL && lexer->is_inhibited == 0
		&& (token->code == TC_LBRACE || token->code == TC_RBRACE))
	{
		if (lexer->is_parenthesized == 0)
		{
			if (token->code == TC_LBRACE)
				lexer->is_parenthesized = TC_LBRACE;
		}
		else if (lexer->is_parenthesized == TC_LBRACE)
		{
			if (token->code == TC_RBRACE)
				lexer->is_parenthesized = 0;
		}
	}
	return (lexer->is_parenthesized);
}

static int		s_analyse_char(t_parser *parser, t_lexer *lexer, char const *s,
					int *i)
{
	t_token		*token;
	int			ret;
	int			is_inhibited;

	token = lexer_token_recognizer(parser, s + *i, *i);
	is_inhibited = s_inhibited_code(lexer, token);
	s_parenthesis_code(lexer, token);
	if (token != NULL && is_inhibited != 0 && token->code != TC_DOLLAR)
	{
		if (lexer_bufferize(lexer, token->op, token->len) != ST_OK)
			return (ST_MALLOC);
		*i += token->len;
	}
	else if (token != NULL && (is_inhibited == 0 || token->code == TC_DOLLAR))
	{
		if ((ret = lexer_buffer_dump(parser, lexer)) != ST_OK)
			return (ret);
		if ((ret = lexer_token_add(lexer, token->op, *token)) != ST_OK)
			return (ret);
		*i += token->len;
	}
	else if (lexer_bufferize(lexer, s + (*i)++, 1) != ST_OK)
		return (ST_MALLOC);
	return (ST_OK);
}

static int		s_return_status(t_parser *parser, t_lexer *lexer)
{
	t_token		*token;
	int			i;

	if (parser->mode == F_PARSING_TERMCAPS)
	{
		if (lexer->is_inhibited != 0)
			return (lexer->is_inhibited);
		if (lexer->is_parenthesized != 0)
			return (lexer->is_parenthesized);
		token = NULL;
		if (parser->lexer->size > 0)
		{
			i = parser->lexer->size - 1;
			while (i > 0 && parser->lexer->tokens[i]->type == TT_SEPARATOR)
				i--;
			token = parser->lexer->tokens[i];
		}
		if (token && (token->code == TC_PIPE || token->code == TC_AND_IF
			|| token->code == TC_OR_IF))
			return (token->code);
		else if (token && token->code == TC_BACKSLASH)
			return (TC_BACKSLASH);
		return (ST_OK);
	}
	return (lexer->is_inhibited != 0 ? ST_LEXER : ST_OK);
}

/*
** Parse string argument chars by chars in order to detect special shell
** operators If no operators are detected, current char will be bufferized
*/

int				lexer_tokenize(const char *s, t_parser *parser, t_lexer *lexer)
{
	int			i;
	int			ret;

	i = 0;
	while (s && s[i])
		if ((ret = s_analyse_char(parser, lexer, s, &i)) != ST_OK)
			return (ret);
	if ((ret = lexer_buffer_dump(parser, lexer)) != ST_OK)
		return (ret);
	return (s_return_status(parser, lexer));
}

#include "parser.h"

/*
** Unstack the list of tokens to do whatever we need during ST_PARSING_NONE:
** -> initialize heredoc (dbl_chev_left redirections)
*/

static int	s_process_tokens(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	while (*i < lexer->size
		&& !(TOKEN_TYPE(*i) == TT_REDIR
			&& TOKEN_CODE(*i) == TC_DLESS)
		&& !((*i + 1 < lexer->size
			&& TOKEN_TYPE(*i) == TT_NAME
			&& TOKEN_TYPE(*i + 1) == TT_REDIR
			&& TOKEN_CODE(*i + 1) == TC_DLESS)))
	{
		ret = lexer->tokens[*i]->parse(NULL, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	if (*i < lexer->size)
	{
		ret = lexer->tokens[*i]->parse(NULL, parser, lexer, i);
		if (ret != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

int			parser_build_list_unstack_lexer_none(t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;

	redir_list_free(&parser->sh->redir_head);
	while (*i < lexer->size)
	{
		if ((ret = s_process_tokens(parser, lexer, i)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

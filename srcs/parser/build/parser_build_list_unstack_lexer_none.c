#include "parser.h"

/*
** Unstack the list of tokens to do whatever we need during ST_PARSING_NONE:
** -> initialize heredoc (dbl_chev_left redirections)
*/

int	parser_build_list_unstack_lexer_none(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;

	// we close old fds and free old list to construct a new one
	redir_list_free(&parser->sh->redir_head);

	while (*i < lexer->size)
	{
		log_info("remaining tokens (none) : %d / %d", lexer->size - *i, lexer->size);
		ret = ST_OK;

		(void)parser;
		while (*i < lexer->size
			&& !(TOKEN_TYPE(*i) == TT_REDIR && TOKEN_CODE(*i) == TC_DLESS)
			&& !((*i + 1 < lexer->size && TOKEN_CODE(*i) == TC_NONE && TOKEN_TYPE(*i + 1) == TT_REDIR && TOKEN_CODE(*i + 1) == TC_DLESS)))
		{
			ret = lexer->tokens[*i]->parse(NULL, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
			(*i)++;
		}

		if (*i < lexer->size)
		{
			log_debug("%d %d", TOKEN_TYPE(*i), TOKEN_CODE(*i));
			ret = lexer->tokens[*i]->parse(NULL, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
		}

	}
	return (ST_OK);
}

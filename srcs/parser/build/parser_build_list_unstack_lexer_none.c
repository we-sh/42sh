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
		log_info("remaining tokens : %d / %d", lexer->size - *i, lexer->size);
		ret = ST_OK;

		(void)parser;
		while (*i < lexer->size
			&& !(lexer->tokens[*i].type == TT_REDIR && lexer->tokens[*i].code == TC_DBL_CHEV_LEFT)
			&& !((*i + 1 < lexer->size && lexer->tokens[*i + 1].type == TT_REDIR && lexer->tokens[*i].code == TC_DBL_CHEV_LEFT)))
		{
			log_debug("%d %d", lexer->tokens[*i].type, lexer->tokens[*i].code);
			//ret = lexer->tokens[*i].parse(NULL, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
			(*i)++;
		}

		if (*i < lexer->size)
		{
			log_debug("%d %d", lexer->tokens[*i].type, lexer->tokens[*i].code);
			ret = lexer->tokens[*i].parse(NULL, parser, lexer, i);
			if (ret != ST_OK)
				return (ret);
		}
		(*i)++;

	}
	return (ST_OK);
}

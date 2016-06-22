#include "parser.h"

int	token_parse_dbl_chev_left(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '<<'", "TT_REDIR");

	log_error("todo !!!");
	return (ST_PARSER);

	// todo: use parsing mode to customize what this function does
	(void)target;
	(void)parser;

	char *left = lexer->tokens[*i].content;
	(*i)++;
	if (lexer->tokens[*i].code != TC_CHEV_RIGHT)
		log_error("parsing in loosing state");
	(*i)++;

	if (ft_strcmp(lexer->tokens[*i].content, "&") == 0)
		(*i)++;

	char *right = lexer->tokens[*i].content;
	(*i)++;

	log_trace("extracting redire %s > %s", left, right);
	return (0);
}

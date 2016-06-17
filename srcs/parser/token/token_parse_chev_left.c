#include "parser.h"

/*
** Case : cat < README
*/

int	token_parse_chev_left(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s '<'", "TT_REDIR");

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
	(void)proc;
	return (0);
}

#include "parser.h"

/*
** The purpose of the function is to unstack a lexer (eg. a stack of tokens)
** to build an Abstract Syntaxic Tree.
*/

int	parser_process_build(t_list *ast_head, t_lexer *lexer, char **envp)
{
	int	st;

	if (!lexer || !ast_head)
		return (ST_EINVAL);
	if ((st = job_build_unstack_lexer(ast_head, lexer, envp)) != ST_OK)
		return (st);
	return (ST_OK);
}

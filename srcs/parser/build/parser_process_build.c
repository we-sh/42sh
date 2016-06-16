#include "parser.h"

/*
** The purpose of the function is to unstack a lexer (eg. a stack of tokens)
** to build an Abstract Syntaxic Tree.
*/

int	parser_process_build(t_list *ast_head, t_lexer *lexer, char **envp)
{
	int		ret;

	if (!lexer || !ast_head)
		return (-1);
	if ((ret = ast_unstack_lexer(ast_head, lexer, envp)) != 0)
		return (ret);
	return (0);
}

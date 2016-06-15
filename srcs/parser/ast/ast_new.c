#include "parser.h"

/*
** Allocate a new AST.
*/

int	ast_new(t_ast **ast)
{
	if (!(*ast = ft_memalloc(sizeof(t_ast))))
		return (-1);
	return (0);
}

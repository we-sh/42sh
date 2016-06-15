#include "parser.h"

/*
** Allocate a new AST root node.
*/

int	ast_job_new(t_node_job **job)
{
	if (!(*job = ft_memalloc(sizeof(t_node_job))))
		return (-1);
	return (0);
}

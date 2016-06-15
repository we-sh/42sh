#include "parser.h"

/*
** Create a new root node to the AST.
*/

int	ast_add_ast_job(t_list *ast_head, t_node_job *job)
{
	log_info("adding the root to the ast...");
	if (!ast || !job)
		return (-1);
	if (!(ast->job))
		ast->job = job;
	else
	{
		while (ast->job->next)
			ast->job = ast->job->next;
		ast->job->next = job;
		job->prev = ast->job;
	}
	return (0);
}

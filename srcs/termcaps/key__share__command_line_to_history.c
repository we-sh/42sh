#include "shell.h"

/*
** Add command_line to history
*/

int						key__share__command_line_to_history(
							t_termcaps_context *context)
{
	t_list_node_history	*new;

	new = list_node__history_create(&context->command_line,
		context->prompt.size);
	if (!new)
	{
		log_error("node__history_create() failed %s", "");
		return (0);
	}
	list_head__insert(&context->history,
						context->history.size,
						&new->list);
	list_head__command_line_destroy(&context->command_line);
	list_head__init(&context->command_line);
	return (1);
}

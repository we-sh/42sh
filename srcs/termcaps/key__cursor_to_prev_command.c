#include "shell.h"

int			key__cursor_to_prev_command(t_internal_context *in_context)
{
	t_list				*history_entry;
	t_list_node_history	*history_node;

	if (in_context->state == STATE_REGULAR)
	{
		if (in_context->history.offset == 0)
			return (1);
		list_head__command_line_destroy(&in_context->command_line);
		list_head__init(&in_context->command_line);
		in_context->command_line.offset = 0;
		in_context->history.offset -= 1;
		history_entry =
			list_nth(&in_context->history.list, in_context->history.offset);
		history_node = CONTAINER_OF(history_entry, t_list_node_history, list);
		list_head__command_line_dup(&in_context->command_line,
									&history_node->command_line);
		in_context->command_line.offset = in_context->command_line.size;
	}
	return (1);
}

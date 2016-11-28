#include "shell.h"

int			key__cursor_to_prev_command(t_termcaps_context *in_context)
{
	t_list			*history_entry;
	t_node_history	*history_node;

	if (in_context->state == STATE_REGULAR)
	{
		if (in_context->history.offset == 0)
			return (1);
		command_clear(&in_context->command);
		list_head__init(&in_context->command);
		in_context->history.offset -= 1;
		history_entry =
			list_nth(&in_context->history.list, in_context->history.offset + 1);
		history_node = CONTAINER_OF(history_entry, t_node_history, list);
		ASSERT(command_add_string(in_context->prompt.size,
											in_context->prompt.bytes,
											&in_context->command));
		ASSERT(command_add_string(history_node->command.size,
											history_node->command.bytes,
											&in_context->command));
		in_context->command.offset = in_context->command.size;
	}
	return (1);
}

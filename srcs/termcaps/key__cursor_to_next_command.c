#include "shell.h"

static int				s_get_next_command(t_termcaps_context *context)
{
	t_list			*history_entry;
	t_node_history	*history_node;

	history_entry = list_nth(&context->history.list,
			context->history.offset + 1);
	history_node = CONTAINER_OF(history_entry,
								t_node_history, list);
	ASSERT(command_add_string(history_node->command.size,
											history_node->command.bytes,
											&context->command));
	context->command.offset = context->command.size;
	return (1);
}

int						key__cursor_to_next_command(t_termcaps_context *context)
{
	if (context->state != STATE_REGULAR)
		return (1);
	if (context->history.offset == context->history.size)
		return (1);
	context->history.offset += 1;
	command_clear(&context->command);
	list_head__init(&context->command);
	ASSERT(command_add_string(context->prompt.size,
											context->prompt.bytes,
											&context->command));
	if (context->history.offset != context->history.size)
	{
		return (s_get_next_command(context));
	}
	return (1);
}

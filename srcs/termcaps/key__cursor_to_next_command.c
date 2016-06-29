#include "shell.h"

static int				s_get_next_command(t_termcaps_context *context)
{
	t_list				*history_entry;
	t_list_node_history	*history_node;

	history_entry = list_nth(&context->history.list,
			context->history.offset + 1);
	history_node = CONTAINER_OF(history_entry,
								t_list_node_history, list);
	ASSERT(termcaps_string_to_command_line(history_node->command_line.size,
											history_node->command_line.bytes,
											&context->command_line));
	context->command_line.offset = context->command_line.size;
	return (1);
}

int						key__cursor_to_next_command(t_termcaps_context *context)
{
	if (context->state != STATE_REGULAR)
		return (1);
	if (context->history.offset == context->history.size)
		return (1);
	context->history.offset += 1;
	list_head__command_line_destroy(&context->command_line);
	list_head__init(&context->command_line);
	ASSERT(termcaps_string_to_command_line(context->prompt.size,
											context->prompt.bytes,
											&context->command_line));
	if (context->history.offset != context->history.size)
	{
		return (s_get_next_command(context));
	}
	return (1);
}

#include "shell.h"

int			key__backspace(t_internal_context *in_context)
{
	t_list *entry;

	if (in_context->state == STATE_REGULAR)
	{
		if (in_context->command_line.offset <= PROMPT_SIZE)
			return (1);
		entry = list_nth(&in_context->command_line.list,
				in_context->command_line.offset);
		list_head__del(&in_context->command_line, entry);
		in_context->command_line.offset--;
		list_node__command_line_destroy(entry);
	}
	return (1);
}

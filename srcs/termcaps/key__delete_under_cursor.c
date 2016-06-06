#include "shell.h"

int		key__delete_under_cursor(t_internal_context *context)
{
	t_list *entry;

	if (context->state == STATE_REGULAR)
	{
		if (context->command_line.size == context->prompt.size)
		{
			context->state = STATE_EXIT;
			context->buffer = ft_strdup("exit");
			return (1);
		}
		if (context->command_line.offset == context->command_line.size)
			return (1);
		entry =
			list_nth(&context->command_line.list, context->command_line.offset);
		list_head__del(&context->command_line, entry);
		list_node__command_line_destroy(entry);
	}
	return (1);
}

#include "shell.h"

int		key__delete_under_cursor(t_termcaps_context *context)
{
	t_list *entry;

	if (context->state == STATE_REGULAR)
	{
		if (context->command_line.size == context->prompt.size)
		{
			context->buffer = ft_strdup("exit");
			return (1);
		}
		if (context->command_line.offset == context->command_line.size)
			return (1);
		entry =
			list_nth(&context->command_line.list, context->command_line.offset + 1);
		list_head__del(&context->command_line, entry);
		list_node__command_line_destroy(entry);
	}
	return (1);
}

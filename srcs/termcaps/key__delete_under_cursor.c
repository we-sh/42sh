#include "shell.h"

int		key__delete_under_cursor(t_termcaps_context *context)
{
	t_list *entry;

	if (context->state == STATE_REGULAR)
	{
		if (context->command.size == context->prompt.size &&
				context->option == OPTION_NONE)
		{
			context->buffer = ft_strdup("exit");
			return (1);
		}
		if (context->command.offset == context->command.size)
			return (1);
		entry = list_nth(&context->command.list,
					context->command.offset + 1);
		list_head__del(&context->command, entry);
		command_del(entry);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		context->state = STATE_REGULAR;
		context->history.offset = context->history.size;
	}
	return (1);
}

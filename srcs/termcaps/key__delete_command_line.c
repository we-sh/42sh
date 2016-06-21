#include "shell.h"

int				key__delete_command_line(t_termcaps_context *context)
{
	t_list_head	head;
	size_t		selection_start;
	size_t		selection_size;

	if (context->state == STATE_REGULAR)
	{
		list_head__command_line_destroy(&context->command_line);
		list_head__init(&context->command_line);
		context->command_line.offset = 0;
		if (!termcaps_string_to_command_line(context->prompt.size,
											context->prompt.bytes,
											&context->command_line))
		{
			log_error("minishell__string_to_command_line() failed %.*s", (int)context->prompt.size, context->prompt.bytes);
			return (0);
		}
		context->history.offset = context->history.size;
	}
	else if (context->state == STATE_SELECTION)
	{
		ft_putstr(SELECTBLANC);
		context->state = STATE_REGULAR;
		key__share__selection_get(context, &selection_start, &selection_size);
		list_head__init(&head);
		list_head__slice(&head, &context->command_line,
						selection_start, selection_size);
		list_head__command_line_destroy(&head);
		context->command_line.offset = selection_start;
	}
	return (1);
}

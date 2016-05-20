#include "shell.h"

int				key__delete_command_line(t_internal_context *context)
{
	t_list_head	head;
	size_t		selection_start;
	size_t		selection_size;

	if (context->state == STATE_REGULAR)
	{
		list_head__command_line_destroy(&context->command_line);
		list_head__init(&context->command_line);
		context->command_line.offset = 0;
		if (!termcaps_string_to_command_line(PROMPT_SIZE, PROMPT, &context->command_line))
			FATAL("minishell__string_to_command_line() failed %s", PROMPT);
		context->history.offset = context->history.size;
	}
	else if (context->state == STATE_SELECTION)
	{
		context->state = STATE_REGULAR;
		key__share__selection_get(context, &selection_start, &selection_size);
		list_head__init(&head);
		list_head__slice(&head, &context->command_line, selection_start, selection_size);
		list_head__command_line_destroy(&head);
	}
	return (1);
}

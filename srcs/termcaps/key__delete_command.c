
#include "shell.h"
static int		s_key_delete_selection(t_termcaps_context *context)
{
	t_list_head	head;
	size_t		selection_start;
	size_t		selection_size;

	ft_putstr(SELECTBLANC);
	context->state = STATE_REGULAR;
	key__share__selection_get(context, &selection_start, &selection_size);
	list_head__init(&head);
	list_head__slice(&head, &context->command,
					selection_start, selection_size);
	command_clear(&head);
	context->command.offset = selection_start;
	return (ST_OK);
}

int				key__delete_command(t_termcaps_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		command_clear(&context->command);
		if (!command_add_string(context->prompt.size,
											context->prompt.bytes,
											&context->command))
			return (0);
		context->history.offset = context->history.size;
	}
	else if (context->state == STATE_SELECTION)
		s_key_delete_selection(context);
	return (1);
}

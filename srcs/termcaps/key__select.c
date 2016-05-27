#include "shell.h"

int		key__select(t_internal_context *in_context)
{
	if (in_context->state == STATE_REGULAR)
	{
		in_context->state = STATE_SELECTION;
		in_context->selection_offset_start = in_context->command_line.offset;
		in_context->selection_offset_end =
			MINISHELL_KEY__SHARE__SELECTION_OFFSET_UNDEFINED;
	}
	else if (in_context->state == STATE_SELECTION)
	{
		in_context->state = STATE_REGULAR;
		in_context->selection_offset_end = in_context->command_line.offset;
	}
	return (1);
}

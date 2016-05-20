#include "shell.h"

int		key__cursor_to_prev_character(t_internal_context *in_context)
{
	if (in_context->command_line.offset <= PROMPT_SIZE)
		return (1);
	in_context->command_line.offset -= 1;
	return (1);
}

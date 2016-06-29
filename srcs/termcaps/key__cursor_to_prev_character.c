#include "shell.h"

int		key__cursor_to_prev_character(t_termcaps_context *context)
{
	if (context->command_line.offset <= context->prompt.size)
		return (1);
	context->command_line.offset -= 1;
	return (1);
}

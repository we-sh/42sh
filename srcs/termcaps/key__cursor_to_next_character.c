#include "shell.h"

int		key__cursor_to_next_character(t_termcaps_context *in_context)
{
	if (in_context->command.offset == in_context->command.size)
		return (1);
	in_context->command.offset += 1;
	return (1);
}

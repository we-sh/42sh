#include "shell.h"

int		key__cursor_to_next_character(t_internal_context *in_context)
{
	if (in_context->command_line.offset == in_context->command_line.size)
		return (1);
	in_context->command_line.offset += 1;
	return (1);
}

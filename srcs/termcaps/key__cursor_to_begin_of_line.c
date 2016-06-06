#include "shell.h"

int		key__cursor_to_begin_of_line(t_internal_context *context)
{
	context->command_line.offset = context->prompt.size;
	return (1);
}

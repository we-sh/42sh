#include "shell.h"

int		key__cursor_to_begin_of_line(t_termcaps_context *context)
{
	context->command.offset = context->prompt.size;
	return (1);
}

#include "shell.h"

int		key__cursor_to_end_of_line(t_termcaps_context *in_context)
{
	in_context->command.offset = in_context->command.size;
	return (1);
}

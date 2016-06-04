#include "shell.h"

int		key__cursor_to_begin_of_line(t_internal_context *in_context)
{
	in_context->command_line.offset = PROMPT_SIZE;
	return (1);
}

#include "shell.h"

int		key__cursor_to_prev_word(t_internal_context *in_context)
{
	key__share__prev_word_offset(&in_context->command_line,
										   in_context->command_line.offset,
										   &in_context->command_line.offset);
	return (1);
}

#include "shell.h"

int		key__cursor_to_prev_word(t_termcaps_context *in_context)
{
	key__share__prev_word_offset(&in_context->command,
								in_context->command.offset,
								in_context->prompt.size,
								&in_context->command.offset);
	return (1);
}

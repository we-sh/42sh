#include "shell.h"

int		key__cursor_to_next_word(t_termcaps_context *in_context)
{
	key__share__next_word_offset(&in_context->command_line,
								in_context->command_line.offset,
								&in_context->command_line.offset);
	return (1);
}

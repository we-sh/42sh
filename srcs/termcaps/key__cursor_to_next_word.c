#include "shell.h"

int		key__cursor_to_next_word(t_termcaps_context *in_context)
{
	key__share__next_word_offset(&in_context->command,
								in_context->command.offset,
								&in_context->command.offset);
	return (1);
}

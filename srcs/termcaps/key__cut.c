#include "shell.h"

int				key__cut(t_internal_context *in_context)
{
	size_t		selection_start;
	size_t		selection_size;

	if (in_context->state == STATE_REGULAR)
	{
		key__share__prev_word_offset(&in_context->command_line,
											   in_context->command_line.offset,
											   &selection_start);
		selection_size = in_context->command_line.offset - selection_start;
	}
	else if (in_context->state == STATE_SELECTION)
	{
		in_context->state = STATE_REGULAR;
		if (!key__share__selection_get(in_context,
												 &selection_start,
												 &selection_size))
			FATAL("key__share__selection_get() failed %s\r", "");
	}
	else
		return (0);
	key__share__cut_build_copy(in_context, selection_start, selection_size);
	return (1);
}

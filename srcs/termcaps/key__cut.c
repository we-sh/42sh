#include "shell.h"

int				key__cut(t_termcaps_context *in_context)
{
	size_t		selection_start;
	size_t		selection_size;

	if (in_context->state == STATE_REGULAR)
	{
		key__share__prev_word_offset(&in_context->command_line,
									in_context->command_line.offset,
									in_context->prompt.size,
									&selection_start);
		selection_size = in_context->command_line.offset - selection_start;
	}
	else if (in_context->state == STATE_SELECTION)
	{
		ft_putstr(SELECTBLANC);
		in_context->state = STATE_REGULAR;
		if (!key__share__selection_get(in_context,
										&selection_start,
										&selection_size))
		{
			log_error("key__share__selection_get() failed %s\r", "");
			return (0);
		}
	}
	else
		return (0);
	key__share__cut_build_copy(in_context, selection_start, selection_size);
	return (1);
}

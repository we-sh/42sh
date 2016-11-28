#include "shell.h"

static int		s_key_cut_selection(t_termcaps_context *in_context,
									size_t *selection_start,
									size_t *selection_size)
{
	ft_putstr(SELECTBLANC);
	in_context->state = STATE_REGULAR;
	if (!key__share__selection_get(in_context,
									selection_start,
									selection_size))
	{
		log_error("key__share__selection_get() failed %s\r", "");
		return (0);
	}
	return (1);
}

int				key__cut(t_termcaps_context *in_context)
{
	size_t		selection_start;
	size_t		selection_size;

	selection_size = 0;
	selection_start = 0;
	if (in_context->state == STATE_REGULAR)
	{
		key__share__prev_word_offset(&in_context->command,
									in_context->command.offset,
									in_context->prompt.size,
									&selection_start);
		selection_size = in_context->command.offset - selection_start;
	}
	else if (in_context->state == STATE_SELECTION)
	{
		ASSERT(s_key_cut_selection(in_context,
								&selection_start, &selection_size));
	}
	else
		return (1);
	key__share__cut_build_copy(in_context, selection_start, selection_size);
	return (1);
}

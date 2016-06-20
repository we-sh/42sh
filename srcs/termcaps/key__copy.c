#include "shell.h"

int			key__copy(t_termcaps_context *in_context)
{
	size_t	copy_start;
	size_t	copy_size;

	if (in_context->state == STATE_SELECTION)
	{
		ft_putstr(SELECTBLANC);
		in_context->state = STATE_REGULAR;
		if (!key__share__selection_get(in_context, &copy_start, &copy_size))
		{
			log_error("key__share__selection_get() failed %s", "");
			return (0);
		}
		if (!key__share__copy_build_copy(&in_context->command_line, copy_start,
					copy_size, &in_context->copy))
		{
			log_error("key__share__copy_build_copy() failed %s", "");
			return (0);
		}
	}
	return (1);
}

# include "shell.h"

int			key__copy(t_internal_context *in_context)
{
	size_t	copy_start;
	size_t	copy_size;

	if (in_context->state == STATE_SELECTION)
	{
		in_context->state = STATE_REGULAR;
		if (key__share__selection_get(in_context, &copy_start, &copy_size) > 0)
			FATAL("key__share__selection_get() failed %s\r", "");
		if (key__share__copy_build_copy(&in_context->command_line, copy_start, copy_size, &in_context->copy) > 0)
			FATAL("key__share__copy_build_copy() failed %s\r", "");
	}
	return (1);
}

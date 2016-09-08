#include "shell.h"

int			key__copy(t_termcaps_context *in_context)
{
	size_t	copy_start;
	size_t	copy_size;

	if (in_context->state != STATE_SELECTION)
		return (1);
	ft_putstr(SELECTBLANC);
	in_context->state = STATE_REGULAR;
	ASSERT(key__share__selection_get(in_context, &copy_start, &copy_size));
	ASSERT(key__share__copy_build_copy(&in_context->command,
										copy_start,
										copy_size,
										&in_context->copy));
	return (1);
}

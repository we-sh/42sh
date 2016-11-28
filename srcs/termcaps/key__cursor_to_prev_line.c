#include "shell.h"

int		key__cursor_to_prev_line(t_termcaps_context *context)
{
	int	distance;

	distance = context->command.offset - caps__win(WIN_COLUMNS);
	if (distance > (int)context->prompt.size)
		context->command.offset = distance;
	else
		context->command.offset = context->prompt.size;
	return (1);
}

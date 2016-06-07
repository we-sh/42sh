#include "shell.h"

int		key__cursor_to_prev_line(t_termcaps_context *context)
{
	int	distance;

	distance = context->command_line.offset - caps__win(WIN_COLUMNS);
	if (distance > (int)context->prompt.size)
		context->command_line.offset = distance;
	else
		context->command_line.offset = context->prompt.size;
	return (1);
}

#include "shell.h"

int		key__cursor_to_next_line(t_termcaps_context *in_context)
{
	int	distance;

	distance = in_context->command.offset + caps__win(WIN_COLUMNS);
	if (distance < (int)in_context->command.size)
		in_context->command.offset = distance;
	else
		in_context->command.offset = in_context->command.size;
	return (1);
}

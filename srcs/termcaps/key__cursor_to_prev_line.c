#include "shell.h"

int		key__cursor_to_prev_line(t_internal_context *in_context)
{
	int	distance;

	distance = in_context->command_line.offset - caps__win(WIN_COLUMNS);
	if (distance > (int)PROMPT_SIZE)
		in_context->command_line.offset = distance;
	else
		in_context->command_line.offset = PROMPT_SIZE;
	return (1);
}

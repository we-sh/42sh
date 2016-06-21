#include "shell.h"

int		key__ctrl_c(t_termcaps_context *context)
{
	ASSERT(termcaps_display_command_line(context));
	(void)write(context->fd, "\n", sizeof("\n") - 1);
	list_head__command_line_destroy(&context->command_line);
	list_head__init(&context->command_line);
	ASSERT(termcaps_string_to_command_line(context->prompt.size,
											context->prompt.bytes,
											&context->command_line));
	return (1);
}

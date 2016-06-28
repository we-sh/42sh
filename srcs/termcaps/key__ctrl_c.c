#include "shell.h"

int		key__ctrl_c(t_termcaps_context *context)
{
	ASSERT(termcaps_display_command_line(context));
	list_head__command_line_destroy(&context->command_line);
	list_head__init(&context->command_line);
	context->buffer = ft_strdup("^C\n");
	return (1);
}

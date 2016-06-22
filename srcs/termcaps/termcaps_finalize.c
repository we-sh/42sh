#include "shell.h"

int		termcaps_finalize(t_termcaps_context *context)
{
	list_head__history_destroy(&context->history);
	list_head__command_line_destroy(&context->command_line);
	list_head__command_line_destroy(&context->copy);
	free(context->prompt.bytes);
	context->is_initialized = 0;
	return (1);
}

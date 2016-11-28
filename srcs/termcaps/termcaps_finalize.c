#include "shell.h"

int		termcaps_finalize(t_termcaps_context *context)
{
	if (!history_write(&context->history, context->history_file, 0))
	{
		log_error("history_write failed");
		return (0);
	}
	history_clear(&context->history);
	command_clear(&context->command);
	command_clear(&context->copy);
	free(context->prompt.bytes);
	context->is_initialized = 0;
	return (1);
}

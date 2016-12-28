#include "shell.h"

void	termcaps_error(t_termcaps_context *context,
		char *cmd, size_t cmd_size, char *msg)
{
	termcaps_display_command(context);
	command_clear(&context->command);
	command_add_string(context->prompt.size, context->prompt.bytes,
						&context->command);
	termcaps_write(2, "\n", sizeof("\n") - 1);
	termcaps_write(2, cmd, cmd_size);
	termcaps_write(2, ": ", sizeof(": ") - 1);
	termcaps_write(2, msg, ft_strlen(msg));
	termcaps_write(2, "\n", sizeof("\n") - 1);
}

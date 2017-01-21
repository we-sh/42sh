#include "shell.h"

int		key__ctrl_c(t_termcaps_context *context)
{
	if (context->state != STATE_REGULAR)
	{
		if (context->state == STATE_SELECTION)
			termcaps_write(context->fd, SELECTBLANC, sizeof(SELECTBLANC) - 1);
		context->state = STATE_REGULAR;
	}
	ASSERT(termcaps_display_command(context));
	command_clear(&context->command);
	list_head__init(&context->command);
	context->buffer = ft_strdup("^C\n");
	return (1);
}

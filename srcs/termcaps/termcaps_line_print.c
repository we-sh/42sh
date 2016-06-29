#include "shell.h"

#define REVERSE_I_SEARCH					"reverse-i-search"
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search") - 1)

int		termcaps_line_print(t_termcaps_context *context,
							t_buffer *history_search)
{
	char		buffer[TERMCAPS_BUFFER_MAX];
	size_t		buffer_size;

	if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
	{
		ASSERT(termcaps_display_command_line(context));
		caps__cursor_to_offset(context->command_line.offset,
							context->command_line.size);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		termcaps_write(context->fd, REVERSE_I_SEARCH, REVERSE_I_SEARCH_SIZE);
		if (list_head__command_line_to_buffer(&context->command_line,
								sizeof(buffer), &buffer_size, buffer))
		{
			termcaps_write(context->fd, " '", sizeof(" '") - 1);
			termcaps_write(context->fd, buffer + context->prompt.size,
										buffer_size - context->prompt.size);
			termcaps_write(context->fd, "' : ", sizeof("' : ") - 1);
		}
		if (termcaps_history_search(context, history_search))
			termcaps_write(context->fd,
						history_search->bytes, history_search->size);
	}
	return (1);
}

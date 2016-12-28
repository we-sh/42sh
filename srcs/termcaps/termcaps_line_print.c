#include "shell.h"

#define REVERSE_I_SEARCH					"reverse-i-search"
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search") - 1)

static int	s_state_history(t_termcaps_context *context,
							t_buffer *history_elem)
{
	char		buffer[TERMCAPS_BUFFER_MAX];
	size_t		buffer_size;

	if (!command_to_buffer(&context->command,
							sizeof(buffer), &buffer_size, buffer))
		return (1);
	buffer_size -= context->prompt.size;
	ft_memmove(buffer, buffer + context->prompt.size, buffer_size);
	termcaps_write(context->fd, REVERSE_I_SEARCH, REVERSE_I_SEARCH_SIZE);
	termcaps_write(context->fd, " '", sizeof(" '") - 1);
	termcaps_write(context->fd, buffer, buffer_size);
	termcaps_write(context->fd, "' : ", sizeof("' : ") - 1);
	if (context->history.offset == 0)
		context->history.offset = context->history.size;
	context->history.offset =
		history_search(&context->history, buffer, buffer_size, -1);
	if (history_get(&context->history, context->history.offset, history_elem))
		termcaps_write(context->fd,
					history_elem->bytes, history_elem->size);
	return (1);
}

static int	s_state_regular(t_termcaps_context *context)
{
	ASSERT(termcaps_display_command(context));
	caps__cursor_to_offset(context->command.offset,
						context->command.size);
	return (1);
}

int			termcaps_line_print(t_termcaps_context *context,
							t_buffer *history_elem)
{
	if (context->state == STATE_REGULAR || context->state == STATE_SELECTION)
	{
		return (s_state_regular(context));
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		return (s_state_history(context, history_elem));
	}
	return (1);
}

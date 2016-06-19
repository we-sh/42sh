#include "shell.h"

static int		s_fill_context_buffer(t_termcaps_context *context, char *buffer)
{
	context->buffer = ft_strdup(buffer + context->prompt.size);
	if (!context->buffer)
		return (0);
	return (1);
}

static int		s_bufferize_input(t_termcaps_context *context)
{
	size_t		buffer_size;
	char		buffer[2048];

	if (!list_head__command_line_to_buffer(&context->command_line,
				sizeof(buffer) - 1, &buffer_size, buffer))
	{
		log_error("list_head__command_line_to_buffer() failed");
		return (0);
	}
	buffer[buffer_size] = '\0';
	if (!s_fill_context_buffer(context, buffer))
	{
		log_error("(s_fill_context_buffer() failed");
		return (0);
	}
	if (!key__share__command_line_to_history(context))
	{
		log_error("key__share__command_line_to_history() failed");
		return (0);
	}
	context->history.offset = context->history.size;
	return (1);
}

int g_child = 0;
int g_in_child = 0;

int				key__send(t_termcaps_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		quoting_new_context(context);
		if (g_child == 0)
		{
			termcaps_display_command_line(context->fd, &context->command_line);
			caps__print_cap(CAPS__CARRIAGE_RETURN, 0);
		}
		if (context->command_line.size > context->prompt.size)
		{
			if (!s_bufferize_input(context))
			{
				log_error("s_bufferize_input() failed");
				return (0);
			}
		}
	}
	g_child = 0;
	return (1);
}

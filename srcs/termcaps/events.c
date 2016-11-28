#include "shell.h"

#define EVENT_NOT_FOUND					"event not found"

static int	s_replace_event(t_termcaps_context *context,
							size_t buf_size_max,
							t_buffer *buf,
							size_t buf_offset)
{
	char		*pt;
	size_t		token_size;
	int			history_index;
	t_buffer	event;
	size_t		size_left;

	pt = buf->bytes + buf_offset;
	if (!event_info(&context->history, pt, &token_size, &history_index) ||
		!history_get(&context->history, history_index, &event))
	{
		termcaps_error(context, pt, token_size, EVENT_NOT_FOUND);
		return (0);
	}
	log_debug("Found event {%.*s}", (int)event.size, event.bytes);
	size_left = buf->size - buf_offset + token_size;
	if (buf_offset + event.size + size_left >= buf_size_max)
	{
		termcaps_error(context, "", 0, "Command line too big");
		return (0);
	}
	ft_memmove(pt + event.size, pt + token_size, size_left);
	ft_memcpy(pt, event.bytes, event.size);
	buf->size += event.size - token_size;
	buf->bytes[buf->size] = '\0';
	log_debug("New command {%.*s}", (int)buf->size, buf->bytes);
	return (event.size);
}

static int	s_replace_command(t_termcaps_context *context,
							t_buffer *buf)
{
	termcaps_display_command(context);
	termcaps_write(context->fd, "\n", sizeof("\n") - 1);
	command_clear(&context->command);
	command_add_string(
			context->prompt.size, context->prompt.bytes, &context->command);
	command_add_string(buf->size, buf->bytes, &context->command);
	return (1);
}

int			replace_events(t_termcaps_context *context,
							const size_t buf_size_max,
							t_buffer *buf)
{
	char		*pt;
	size_t		buf_offset;
	size_t		event_size;
	int			no_event;

	no_event = 1;
	buf_offset = 0;
	while ((pt = ft_memchr(
				buf->bytes + buf_offset, '!', buf->size - buf_offset)) != NULL)
	{
		buf_offset = pt - buf->bytes;
		if (ft_isspace(pt[1]) || buf_offset + 1 >= buf->size)
		{
			buf_offset++;
			continue ;
		}
		event_size = s_replace_event(context, buf_size_max, buf, buf_offset);
		if (event_size == 0)
			return (0);
		buf_offset += event_size;
		no_event = 0;
	}
	if (!no_event)
		s_replace_command(context, buf);
	return (no_event);
}

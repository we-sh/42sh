#include "shell.h"

static int  s_next_word(char *s, size_t s_size, size_t *start, size_t *size)
{
    size_t  i;

    i = 0;
    while (i < s_size)
    {
        if (!ft_isspace(s[i]))
            break ;
        i++;
    }
    *start = i;
    if (i == s_size)
        return (0);
    while (i < s_size)
    {
        if (ft_isspace(s[i]))
            break ;
        i++;
    }
    *size = i - *start;
    log_debug("word {%.*s}", (int)*size, s + *start);
    return (1);
}

static int  s_event_word(t_event *info, t_buffer *event)
{
    size_t      word_count;
    size_t      start;
    size_t      size;

    log_debug("info->word %d", info->word);
    word_count = 0;
    if (info->word == WORD_ALL)
        return (1);
    if (info->word == WORD_ARGS)
    {
        s_next_word(event->bytes, event->size, &start, &size);
        event->bytes += start + size;
        event->size -= start + size;
        s_next_word(event->bytes, event->size, &start, &size);
        event->bytes += start;
        event->size -= start;
    }
    else if (info->word == -1)
    {
        start = event->size;
        while (start > 0 && !ft_isspace(event->bytes[start]))
            start--;
        if (start > 0)
            start++;
        event->bytes += start;
        event->size -= start;
    }
    else if (info->word >= 0)
    {
        while (s_next_word(event->bytes, event->size, &start, &size))
        {
            if (word_count == (size_t)info->word)
            {
                event->bytes += start;
                event->size = size;
                return (1);
            }
            event->bytes += start + size;
            event->size -= start + size;
            word_count++;
        }
        return (0);
    }
    log_debug("Found event word {%.*s}", (int)event->size, event->bytes);
    return (1);
}

#define EVENT_NOT_FOUND					"event not found"

static int	s_replace_event(t_termcaps_context *context,
							size_t buf_size_max,
							t_buffer *buf,
							size_t buf_offset)
{
	char		*pt;
    t_event     info;
	t_buffer	event;
	size_t		size_left;

	pt = buf->bytes + buf_offset;
	if (!event_info(&context->history, pt, &info) ||
		!history_get(&context->history, info.history_index, &event) ||
        !s_event_word(&info, &event))
	{
		termcaps_error(context, pt, info.token_size, EVENT_NOT_FOUND);
		return (0);
	}
	size_left = buf->size - buf_offset + info.token_size;
	if (buf_offset + event.size + size_left >= buf_size_max)
	{
		termcaps_error(context, "", 0, "Command line too big");
		return (0);
	}
	ft_memmove(pt + event.size, pt + info.token_size, size_left);
	ft_memcpy(pt, event.bytes, event.size);
	buf->size += event.size - info.token_size;
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

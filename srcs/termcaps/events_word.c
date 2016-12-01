#include "shell.h"

static int	s_next_word(char *s, size_t s_size, size_t *start, size_t *size)
{
	size_t	i;

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
	return (1);
}

static int	s_event_word_args(t_buffer *event)
{
	size_t	start;
	size_t	size;

	s_next_word(event->bytes, event->size, &start, &size);
	event->bytes += start + size;
	event->size -= start + size;
	s_next_word(event->bytes, event->size, &start, &size);
	event->bytes += start;
	event->size -= start;
	return (event->size > 0);
}

static int	s_event_last_word(t_buffer *event)
{
	size_t	start;

	start = event->size;
	while (start > 0 && !ft_isspace(event->bytes[start]))
		start--;
	if (start > 0)
		start++;
	event->bytes += start;
	event->size -= start;
	return (event->size > 0);
}

static int	s_event_word_nth(t_buffer *event, size_t nth)
{
	size_t	word_count;
	size_t	start;
	size_t	size;

	word_count = 0;
	while (s_next_word(event->bytes, event->size, &start, &size))
	{
		if (word_count == nth)
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

int			event_word(t_event *info, t_buffer *event)
{
	int	ret;

	ret = 1;
	if (info->word == WORD_ALL)
		return (1);
	if (info->word == WORD_ARGS)
		ret = s_event_word_args(event);
	else if (info->word == -1)
		ret = s_event_last_word(event);
	else if (info->word >= 0)
		ret = s_event_word_nth(event, (size_t)info->word);
	return (ret);
}

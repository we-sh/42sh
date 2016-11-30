#include "shell.h"

static int	s_count(const char *s, int (*test)(int c), int expected)
{
	int	i;

	i = 0;
	while (s[i] && test(s[i]) == expected)
		i++;
	return (i);
}

static int  s_get_word(const char *pt, int *word)
{
   if (pt[0] == '^')
   {
       *word = 1;
       return (sizeof("^") - 1);
   }
   if (pt[0] == '$')
   {
        *word = -1;
        return (sizeof("$") - 1);
   }
   if (pt[0] == '*')
   {
       *word = WORD_ARGS;
       return (sizeof("*") - 1);
   }
   if (ft_isdigit(pt[0]))
   {
       *word = ft_atoi(pt);
       return (s_count(pt, ft_isdigit, 1));
   }
   return (0);
}

static int	s_event_search(t_list_head *history,
							const char *pt,
                            t_event *event)
{
	if (ft_isalpha(pt[1]))
	{
		event->token_size = 1 + s_count(pt + 1, ft_isalpha, 1);
		event->history_index =
			history_search_prefix(history, pt + 1, event->token_size - 1, -1);
	}
	else if (pt[1] == '?' && ft_isalpha(pt[2]))
	{
		event->token_size = 2 + s_count(pt + 2, ft_isalpha, 1);
		event->history_index =
			history_search(history, pt + 2, event->token_size - 2, -1);
	}
	else
		return (0);
	return (1);
}

static int  s_event_index(const char *pt, t_event *event)
{
	if (ft_isdigit(pt[1]))
    {
		event->token_size = 1 + s_count(pt + 1, ft_isdigit, 1);
		event->history_index = ft_atoi(pt + 1);
    }
    else if (pt[1] == '-' && ft_isdigit(pt[2]))
    {
		event->token_size = 2 + s_count(pt + 2, ft_isdigit, 1);
		event->history_index = ft_atoi(pt + 1);
    }
    else
        return (0);
    return (1);
}

static int  s_event_prev(const char *pt, t_event *event)
{
	if (pt[1] == '!')
	{
		event->token_size = 2;
		event->history_index = -1;
	}
    else if (pt[1] == '^' || pt[1] == '$' || pt[1] == '*')
    {
		event->token_size = 2;
		event->history_index = -1;
        s_get_word(pt + 1, &event->word);
    }
    else
        return (0);
    return (1);
}

int			event_info(t_list_head *history,
						const char *pt,
                        t_event *event)
{
	event->token_size = 0;
	event->history_index = 0;
    event->word = WORD_ALL;
    if (!s_event_index(pt, event) &&
        !s_event_prev(pt, event) &&
	    !s_event_search(history, pt, event))
    {
        event->token_size = s_count(pt, ft_isspace, 0);
        return (0);
    }
    if (pt[event->token_size] == ':')
    {
        event->token_size += 1;
        event->token_size += s_get_word(pt + event->token_size, &event->word);
    }
    return (1);
}

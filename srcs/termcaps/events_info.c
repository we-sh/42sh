#include "shell.h"

static int	s_count(const char *s, int (*test)(int c), int expected)
{
	int	i;

	i = 0;
	while (s[i] && test(s[i]) == expected)
		i++;
	return (i);
}

static int	s_event_info_search(t_list_head *history,
								const char *pt,
								size_t *token_size,
								int *history_index)
{
	if (ft_isalpha(pt[1]))
	{
		*token_size = 1 + s_count(pt + 1, ft_isalpha, 1);
		*history_index =
			history_search_prefix(history, pt + 1, *token_size - 1, -1);
	}
	else if (pt[1] == '?' && ft_isalpha(pt[2]))
	{
		*token_size = 2 + s_count(pt + 2, ft_isalpha, 1);
		*history_index =
			history_search(history, pt + 2, *token_size - 2, -1);
	}
	else
		return (0);
	return (1);
}

int			event_info(t_list_head *history,
						const char *pt,
						size_t *token_size,
						int *history_index)
{
	*token_size = 0;
	*history_index = 0;
	if (ft_isdigit(pt[1]))
	{
		*token_size = 1 + s_count(pt + 1, ft_isdigit, 1);
		*history_index = ft_atoi(pt + 1);
	}
	else if (pt[1] == '-' && ft_isdigit(pt[2]))
	{
		*token_size = 2 + s_count(pt + 2, ft_isdigit, 1);
		*history_index = ft_atoi(pt + 1);
	}
	else if (pt[1] == '!')
	{
		*token_size = 2;
		*history_index = -1;
	}
	else if (!s_event_info_search(history, pt, token_size, history_index))
	{
		*token_size = s_count(pt, ft_isspace, 0);
		return (0);
	}
	return (1);
}

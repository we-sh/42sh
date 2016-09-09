#include "shell.h"

/*
** history search
*/

int					history_search(t_list_head *history,
		const char *str, const size_t size, int direction)
{
	t_list			*pos;
	t_node_history	*node_history;
	size_t			history_offset;
	size_t			i;

	ASSERT(size > 0 && direction != 0);
	history_offset = history->offset;
	pos = list_nth(&history->list, history_offset + 1);
	while (1)
	{
		pos = direction < 0 ? pos->prev : pos->next;
		ASSERT(pos != &history->list);
		node_history = CONTAINER_OF(pos, t_node_history, list);
		i = 0;
		while (node_history->command.size - i >= size)
		{
			if (!ft_memcmp(node_history->command.bytes + i, str, size))
				return (history_offset);
			i++;
		}
		history_offset--;
	}
	return (0);
}

/*
** history search prefix
*/

int					history_search_prefix(t_list_head *history,
		const char *str, const size_t size, int direction)
{
	t_list			*pos;
	t_node_history	*node_history;
	size_t			history_offset;

	ASSERT(size > 0 && direction != 0);
	history_offset = history->offset;
	pos = list_nth(&history->list, history_offset + 1);
	while (1)
	{
		if (direction < 0)
			pos = pos->prev;
		else if (direction > 0)
			pos = pos->next;
		ASSERT(pos != &history->list);
		node_history = CONTAINER_OF(pos, t_node_history, list);
		if (size <= node_history->command.size &&
				!ft_memcmp(node_history->command.bytes, str, size))
			return (history_offset);
		history_offset--;
	}
	return (0);
}

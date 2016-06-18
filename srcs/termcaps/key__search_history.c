#include "shell.h"
#include "list_head.h"

int	list_head__history_search(const t_list_head *history, const t_list_head *cmd, t_list_head *match_head)
{
	t_list_node_history	*history;
	t_list				*pos;

	list_head__init(match_head);
	pos = list_nth(&history->list, history->offset);
	if (pos == &history->list)
		return (1);
	while ((pos = pos->prev) && pos != &history->list)
	{
		history = CONTAINER_OF(pos, t_list_node_history, list);
		if (list_head__command_line_match(&history->command_line, &command_line))
		{
			list_head__command_line_dup(match_head, &history->command_line);
			return (1);
		}
	}
	return (0);
}

#define REVERSE_I_SEARCH					"reverse-i-search:"
#define REVERSE_I_SEARCH_SIZE		(sizeof("reverse-i-search:") - 1)

int	key__search_history(t_termcaps_context *context)
{
	return (1);
}

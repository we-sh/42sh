#include "shell.h"

/*
** history add
*/

int					history_add(const char *cmd, t_list_head *history)
{
	t_node_history	*new;
	size_t					cmd_size;

	cmd_size = ft_strlen(cmd);
	new = malloc(sizeof(t_node_history) + cmd_size + 1);
	if (!new)
		return (0);
	new->command.size = cmd_size;
	new->command.bytes = (void *)new + sizeof(t_node_history);
	ft_memcpy(new->command.bytes, cmd, cmd_size);
	new->command.bytes[cmd_size] = '\0';
	list_head__insert(history, history->offset, &new->list);
	return (1);
}

/*
** history clear
*/

void					history_clear(t_list_head *history)
{
	t_list				*pos;
	t_list				*pos_safe;
	t_node_history	*node_history;

	pos_safe = history->list.next;
	while ((pos = pos_safe) && pos != &history->list)
	{
		pos_safe = pos_safe->next;
		node_history = CONTAINER_OF(pos, t_node_history, list);
		free(node_history);
	}
}

/*
** history search
*/

int						history_search(t_list_head *history, const char *str)
{
	t_list				*pos;
	t_node_history	*node_history;
	size_t				history_offset;

	history_offset = history->offset;
	pos = list_nth(&history->list, history_offset + 1);
	while ((pos = pos->prev) && pos != &history->list)
	{
		node_history = CONTAINER_OF(pos, t_node_history, list);
		if (ft_strstr(node_history->command.bytes, str))
			return (history_offset);
		history_offset--;
	}
	return (0);
}

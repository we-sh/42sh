#include "shell.h"

/*
** history add
*/

t_node_history		*history_add(const char *cmd, t_list_head *history)
{
	t_node_history	*new;
	size_t			cmd_size;

	cmd_size = ft_strlen(cmd);
	new = malloc(sizeof(t_node_history) + cmd_size + 1);
	if (!new)
		return (NULL);
	new->command.size = cmd_size;
	new->command.bytes = (void *)new + sizeof(t_node_history);
	ft_memcpy(new->command.bytes, cmd, cmd_size);
	new->command.bytes[cmd_size] = '\0';
	new->is_modified = 0;
	list_head__insert(history, history->size, &new->list);
	return (new);
}

/*
** history clear
*/

void				history_clear(t_list_head *history)
{
	t_list			*pos;
	t_list			*pos_safe;
	t_node_history	*node_history;

	pos_safe = history->list.next;
	while ((pos = pos_safe) && pos != &history->list)
	{
		pos_safe = pos_safe->next;
		node_history = CONTAINER_OF(pos, t_node_history, list);
		free(node_history);
	}
	list_head__init(history);
}

/*
** history get
*/

#define ABS(x) (size_t)((x) < 0 ? -(x) : (x))

int					history_get(t_list_head *history, const int index,
													t_buffer *out_history_elem)
{
	t_list			*pos;
	t_node_history	*node_history;

	out_history_elem->size = 0;
	out_history_elem->bytes = NULL;
	ASSERT(ABS(index) <= history->size);
	pos = list_nth(&history->list, index);
	ASSERT(pos != &history->list);
	node_history = CONTAINER_OF(pos, t_node_history, list);
	*out_history_elem = node_history->command;
	return (1);
}

/*
** history remove
*/

void				history_remove(t_list_head *history, const int index)
{
	t_list			*pos;
	t_node_history	*node_history;

	if ((size_t)index > history->size)
		return ;
	pos = list_nth(&history->list, index);
	if (pos != &history->list)
	{
		node_history = CONTAINER_OF(pos, t_node_history, list);
		list_del(pos);
		free(node_history);
		history->size -= 1;
		if (history->offset >= (size_t)index)
			history->offset -= 1;
	}
}

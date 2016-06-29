#include "shell.h"

/*
** list node history
*/

t_list_node_history		*list_node__history_create(t_list_head *command_line,
													size_t index)
{
	void				*addr;
	t_list_node_history	*new;
	char				buffer[TERMCAPS_BUFFER_MAX];
	size_t				buffer_size;

	ASSERT(list_head__command_line_to_buffer(command_line,
											sizeof(buffer) - 1,
											&buffer_size,
											buffer));
	addr = malloc(sizeof(t_list_node_history) + buffer_size + 1 - index);
	if (!addr)
		return (NULL);
	new = addr;
	new->command_line.bytes = addr + sizeof(t_list_node_history);
	new->command_line.size = buffer_size - index;
	ft_memcpy(new->command_line.bytes, buffer + index, buffer_size - index);
	new->command_line.bytes[buffer_size - index] = 0;
	INIT_LIST_HEAD(&new->list);
	return (new);
}

/*
** list head history
*/

void					list_head__history_destroy(t_list_head *head)
{
	t_list				*pos;
	t_list				*pos_safe;
	t_list_node_history	*node_history;

	pos_safe = head->list.next;
	while ((pos = pos_safe) && pos != &head->list)
	{
		pos_safe = pos_safe->next;
		node_history = CONTAINER_OF(pos, t_list_node_history, list);
		free(node_history);
	}
}

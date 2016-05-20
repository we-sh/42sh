#include "shell.h"

/*
** list node history
*/
t_list_node_history	*list_node__history_create(t_list_head *command_line)
{
	t_list_node_history	*new;

	if (!command_line)
	{
		LOG_ERROR("command_line %p", (void *)command_line);
		return (NULL);
	}
	new = (t_list_node_history *)malloc(sizeof(t_list_node_history));
	if (!new)
	{
		LOG_ERROR("malloc() failed %s", "");
		return (NULL);
	}
	new->command_line.size = command_line->size;
	new->command_line.offset = 0;
	INIT_LIST_HEAD(&new->list);
	INIT_LIST_HEAD(&new->command_line.list);
	list_splice(&command_line->list, &new->command_line.list);
	return (new);
}

/*
** list head history
*/
void			list_head__history_destroy(t_list_head *head)
{
	t_list				*pos;
	t_list				*pos_safe;
	t_list_node_history	*node_history;

	pos_safe = head->list.next;
	while ((pos = pos_safe) && pos != &head->list)
	{
		pos_safe = pos_safe->next;
		node_history = CONTAINER_OF(pos, t_list_node_history, list);
		list_head__command_line_destroy(&node_history->command_line);
		free(node_history);
	}
}

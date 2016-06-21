#include "shell.h"

/*
** list node command line
*/

t_list_node_cmd		*list_node__command_line_create(const size_t character_size,
													const char *character)
{
	t_list_node_cmd	*new;

	if (!character_size || character_size > CHARACTER_SIZE_MAX || !character)
	{
		log_error("character_size %zu size_max %zu character %p",
			character_size, CHARACTER_SIZE_MAX, (void *)character);
		return (NULL);
	}
	new = (t_list_node_cmd *)malloc(sizeof(t_list_node_cmd));
	if (!new)
	{
		log_error("malloc() failed %s", "");
		return (NULL);
	}
	INIT_LIST_HEAD(&new->list);
	new->character_size = character_size;
	ft_memcpy(new->character, character, character_size);
	return (new);
}

void				list_node__command_line_destroy(t_list *entry)
{
	t_list_node_cmd	*node;

	node = CONTAINER_OF(entry, t_list_node_cmd, list);
	free(node);
}

/*
** list head command line
** dup
** destroy
** to buffer
*/

t_list_head			*list_head__command_line_dup(t_list_head *dst,
												t_list_head *src)
{
	t_list			*pos;
	t_list_node_cmd	*cur;
	t_list_node_cmd	*new;
	size_t			offset;

	list_head__init(dst);
	offset = 0;
	LIST_FOREACH(&src->list, pos)
	{
		cur = CONTAINER_OF(pos, t_list_node_cmd, list);
		new = list_node__command_line_create(cur->character_size,
			cur->character);
		if (!new)
		{
			log_error("list_node__command_line_create() failed");
			return (0);
		}
		list_head__insert(dst, offset, &new->list);
		offset++;
	}
	return (dst);
}

void				list_head__command_line_destroy(t_list_head *head)
{
	t_list			*pos;
	t_list			*pos_safe;
	t_list_node_cmd	*node_cmd;

	pos_safe = head->list.next;
	while ((pos = pos_safe) && pos != &head->list)
	{
		pos_safe = pos_safe->next;
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		free(node_cmd);
	}
}

int					list_head__command_line_to_buffer(const t_list_head *head,
												const size_t buffer_size_max,
												size_t *buffer_size,
												char *buffer)
{
	size_t			buffer_offset;
	t_list			*pos;
	t_list_node_cmd *node_cmd;

	buffer_offset = 0;
	LIST_FOREACH(&head->list, pos)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (buffer_offset + node_cmd->character_size >= buffer_size_max)
		{
			buffer[buffer_offset - 1] = '$';
			break ;
		}
		ft_memcpy(buffer + buffer_offset, node_cmd->character,
			node_cmd->character_size);
		buffer_offset += node_cmd->character_size;
	}
	*buffer_size = buffer_offset;
	return (1);
}

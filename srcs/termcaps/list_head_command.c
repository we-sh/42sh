#include "shell.h"

/*
** command add
*/

int					command_add(const size_t character_size,
								const char *character,
								t_list_head *command)
{
	t_node_cmd	*new;

	if (!character_size || character_size > CHARACTER_SIZE_MAX || !character)
		return (0);
	ASSERT(new = (t_node_cmd *)malloc(sizeof(t_node_cmd)));
	new->character_size = character_size;
	ft_memcpy(new->character, character, character_size);
	list_head__insert(command,
						command->offset,
						&new->list);
	return (1);
}

/*
** command del
*/

void				command_del(t_list *entry)
{
	t_node_cmd	*node;

	node = CONTAINER_OF(entry, t_node_cmd, list);
	free(node);
}

/*
** command clear
*/

void				command_clear(t_list_head *command)
{
	t_list			*pos;
	t_list			*pos_safe;

	pos_safe = command->list.next;
	while ((pos = pos_safe) && pos != &command->list)
	{
		pos_safe = pos_safe->next;
		command_del(pos);
	}
	list_head__init(command);
}

/*
** list head command line
** dup
** destroy
** to buffer
*/

t_list_head			*command_dup(t_list_head *dst,
								t_list_head *src)
{
	t_list			*pos;
	t_node_cmd		*cur;
	t_list			*safe;

	list_head__init(dst);
	safe = src->list.next;
	while ((pos = safe) && pos != &src->list)
	{
		safe = safe->next;
		cur = CONTAINER_OF(pos, t_node_cmd, list);
		ASSERT(command_add(cur->character_size, cur->character, dst));
	}
	return (dst);
}

int					command_to_buffer(const t_list_head *head,
									const size_t buffer_size_max,
									size_t *buffer_size,
									char *buffer)
{
	size_t			buffer_offset;
	t_list			*pos;
	t_node_cmd		*node_cmd;

	buffer_offset = 0;
	pos = &((t_list_head *)head)->list;
	while ((pos = pos->next) && pos != &head->list)
	{
		node_cmd = CONTAINER_OF(pos, t_node_cmd, list);
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

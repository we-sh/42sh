#include "shell.h"

int						key__share__copy_build_copy(
											t_list_head *command,
											size_t copy_start,
											size_t copy_size,
											t_list_head *out_copy)
{
	t_list				*pos;
	size_t				copy_offset;
	t_node_cmd		*node;

	command_clear(out_copy);
	pos = list_nth(&command->list, copy_start + 1);
	copy_offset = 0;
	while (copy_offset < copy_size)
	{
		node = CONTAINER_OF(pos, t_node_cmd, list);
		ASSERT(command_add(node->character_size, node->character, out_copy));
		pos = pos->next;
		copy_offset++;
	}
	return (1);
}

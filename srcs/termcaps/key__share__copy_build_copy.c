#include "shell.h"

int						key__share__copy_build_copy(
											t_list_head *command_line,
											size_t copy_start,
											size_t copy_size,
											t_list_head *out_copy)
{
	t_list				*pos;
	size_t				copy_offset;
	t_list_node_cmd		*node;
	t_list_node_cmd		*new;

	list_head__command_line_destroy(out_copy);
	list_head__init(out_copy);
	pos = list_nth(&command_line->list, copy_start + 1);
	copy_offset = 0;
	while (copy_offset < copy_size)
	{
		node = CONTAINER_OF(pos, t_list_node_cmd, list);
		new = list_node__command_line_create(node->character_size,
											node->character);
		if (!new)
		{
			log_error("list_node__command_line_create() failed %s", "");
			return (0);
		}
		list_head__insert(out_copy, copy_offset, &new->list);
		pos = pos->next;
		copy_offset++;
	}
	return (1);
}

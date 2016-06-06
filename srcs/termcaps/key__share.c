#include "shell.h"

/*
** Add command_line to history
*/
int		key__share__command_line_to_history(t_internal_context *in_context)
{
	t_list_node_history	*new;

	new = list_node__history_create(&in_context->command_line);
	if (!new)
	{
		log_error("node__history_create() failed %s", "");
		return (0);
	}
	list_head__insert(&in_context->history,
					in_context->history.size, &new->list);
	list_head__init(&in_context->command_line);
	in_context->command_line.offset = 0;
	return (1);
}

/*
** Get the selection
*/
int		key__share__selection_get(t_internal_context *in_context,
										size_t *out_selection_start,
										size_t *out_selection_size)
{
	if (in_context->selection_offset_start ==
			MINISHELL_KEY__SHARE__SELECTION_OFFSET_UNDEFINED)
	{
		log_error("selection offset start is undefined %s", "");
		return (0);
	}
	if (in_context->selection_offset_start < in_context->command_line.offset)
	{
		*out_selection_start = in_context->selection_offset_start;
		*out_selection_size = in_context->command_line.offset -
								in_context->selection_offset_start;
	}
	else
	{
		*out_selection_start = in_context->command_line.offset;
		*out_selection_size = in_context->selection_offset_start -
								in_context->command_line.offset;
	}
	return (1);
}

int			key__share__copy_build_copy(t_list_head *command_line,
											size_t copy_start,
											size_t copy_size,
											t_list_head *out_copy)
{
	t_list			*pos;
	size_t			copy_offset;
	t_list_node_cmd	*node;
	t_list_node_cmd	*new;

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

void		key__share__cut_build_copy(t_internal_context *in_context,
											size_t selection_start,
											size_t selection_size)
{
	list_head__command_line_destroy(&in_context->copy);
	list_head__init(&in_context->copy);
	list_head__slice(&in_context->copy,
					&in_context->command_line,
					selection_start,
					selection_size);
	in_context->command_line.offset = selection_start;
}

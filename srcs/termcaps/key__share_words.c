#include "shell.h"

/*
** Get the NEXT / PREV word offset
*/
#define ISSPACE(node) (node->character_size==1&&ft_isspace(node->character[0]))

void		key__share__prev_word_offset(const t_list_head *command_line,
										size_t current_offset,
										size_t prompt_size,
										size_t *out_offset)
{
	t_list				*pos;
	t_list_node_cmd		*node_cmd;
	enum {
		STATE_UNDEFINED,
		STATE_ALNUM
	}					state;

	pos = list_nth(&command_line->list, current_offset);
	state = STATE_UNDEFINED;
	while (current_offset > prompt_size)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (state == STATE_UNDEFINED && !ISSPACE(node_cmd))
			state = STATE_ALNUM;
		if (state == STATE_ALNUM && ISSPACE(node_cmd))
			break ;
		pos = pos->prev;
		current_offset--;
	}
	*out_offset = current_offset;
}

void		key__share__next_word_offset(const t_list_head *command_line,
										size_t current_offset,
										size_t *out_offset)
{
	t_list			*pos;
	t_list_node_cmd	*node_cmd;
	enum {
		STATE_UNDEFINED,
		STATE_ISSPACE
	}				state;

	pos = list_nth(&command_line->list, current_offset + 1);
	state = STATE_UNDEFINED;
	while (current_offset < command_line->size)
	{
		node_cmd = CONTAINER_OF(pos, t_list_node_cmd, list);
		if (state == STATE_UNDEFINED && ISSPACE(node_cmd))
			state = STATE_ISSPACE;
		if (state == STATE_ISSPACE && !ISSPACE(node_cmd))
			break ;
		pos = pos->next;
		current_offset++;
	}
	*out_offset = current_offset;
}

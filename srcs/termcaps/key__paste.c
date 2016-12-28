#include "shell.h"

int				key__paste(t_termcaps_context *in_context)
{
	t_list		*pos;
	t_list_head	dup;

	if (in_context->state != STATE_REGULAR)
		return (1);
	pos = list_nth(&in_context->command.list,
					in_context->command.offset);
	command_dup(&dup, &in_context->copy);
	list_splice(&dup.list, pos);
	in_context->command.size += dup.size;
	in_context->command.offset += dup.size;
	return (1);
}

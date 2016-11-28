#include "shell.h"

void					key__share__cut_build_copy(
											t_termcaps_context *in_context,
											size_t selection_start,
											size_t selection_size)
{
	command_clear(&in_context->copy);
	list_head__init(&in_context->copy);
	list_head__slice(&in_context->copy,
					&in_context->command,
					selection_start,
					selection_size);
	in_context->command.offset = selection_start;
}

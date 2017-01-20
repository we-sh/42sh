#include "shell.h"

/*
** Get the selection
*/

int						key__share__selection_get(
										t_termcaps_context *in_context,
										size_t *out_selection_start,
										size_t *out_selection_size)
{
	if (in_context->selection_offset_start ==
			MINISHELL_KEY__SHARE__SELECTION_OFFSET_UNDEFINED)
		return (0);
	if (in_context->selection_offset_start < in_context->command.offset)
	{
		*out_selection_start = in_context->selection_offset_start;
		*out_selection_size = in_context->command.offset -
								in_context->selection_offset_start;
	}
	else
	{
		*out_selection_start = in_context->command.offset;
		*out_selection_size = in_context->selection_offset_start -
								in_context->command.offset;
	}
	return (1);
}

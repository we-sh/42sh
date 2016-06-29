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

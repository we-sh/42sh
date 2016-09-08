#include "shell.h"

void			termcaps_line_erase(t_termcaps_context *context,
									const t_buffer history_search)
{
	if (context->state == STATE_SEARCH_HISTORY)
	{
		caps__delete_line(history_search.size +
						context->command.size - context->prompt.size +
						sizeof("reverse-i-search '' : ") - 2);
	}
	else
	{
		caps__delete_line(context->command.offset);
	}
}

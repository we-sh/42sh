#include "shell.h"
#include "list_head.h"

int	key__search_history(t_termcaps_context *context)
{
	if (context->state == STATE_SEARCH_HISTORY)
	{
		if (context->history.offset > 0)
			context->history.offset--;
	}
	else
	{
		context->state = STATE_SEARCH_HISTORY;
	}
	return (1);
}

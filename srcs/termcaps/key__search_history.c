#include "shell.h"
#include "list_head.h"

int	key__search_history(t_termcaps_context *context)
{
	context->state = STATE_SEARCH_HISTORY;
	return (1);
}

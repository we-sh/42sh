#include "shell.h"

int		key__clear(t_termcaps_context *context)
{
	(void)context;
	caps__print_cap(CAPS__HOME_CLEAR, caps__win(WIN_LINE));
	return (1);
}

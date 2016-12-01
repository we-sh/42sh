#include "shell.h"

void	read_history(t_sh *sh, int new)
{
	size_t	offset;

	offset = new ? sh->termcaps_context.history_initial_size : 0;
	history_load(sh->envp, &sh->termcaps_context.history, &offset);
	sh->termcaps_context.history_initial_size = offset;
}

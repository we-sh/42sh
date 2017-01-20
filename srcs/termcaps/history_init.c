#include "shell.h"

int		history_init(t_sh *sh)
{
	INIT_LIST_HEAD(&sh->termcaps_context.history.list);
	sh->termcaps_context.history.size = 0;
	sh->termcaps_context.history.offset = 0;
	sh->termcaps_context.history_initial_size = 0;
	if (!history_load(sh->envp, &sh->termcaps_context.history,
				&sh->termcaps_context.history_initial_size))
		return (0);
	return (1);
}

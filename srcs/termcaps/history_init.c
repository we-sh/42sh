#include "shell.h"

int		history_init(t_sh *sh)
{
	log_debug("Hello wold");
	INIT_LIST_HEAD(&sh->termcaps_context.history.list);
	sh->termcaps_context.history.size = 0;
	sh->termcaps_context.history.offset = 0;
	sh->termcaps_context.history_initial_size = 0;
	if (!history_load(sh->envp, &sh->termcaps_context.history,
				&sh->termcaps_context.history_initial_size))
	{
		log_error("history_load failed");
		return (0);
	}
	return (1);
}

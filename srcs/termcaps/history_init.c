#include "shell.h"

int		history_init(t_sh *sh)
{
    log_debug("Hello wold");
	INIT_LIST_HEAD(&context->history.list);
	context->history.size = 0;
	context->history.offset = 0;
	context->history_initial_size = 0;
	if (!history_load(sh->envp, &context->history, &context->history_initial_size))
	{
		log_error("history_load failed");
		return (0);
	}
	return (1);
}

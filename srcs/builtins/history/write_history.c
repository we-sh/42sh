#include "shell.h"

void	write_history(t_sh *sh, int append)
{
	t_node_history	*node;
	t_list			*pos;

	history_write(sh->envp, &sh->termcaps_context.history, append);
	sh->termcaps_context.history_initial_size =
		sh->termcaps_context.history.size;
	pos = &sh->termcaps_context.history.list;
	while ((pos = pos->next) && pos != &sh->termcaps_context.history.list)
	{
		node = CONTAINER_OF(pos, t_node_history, list);
		node->is_modified = 0;
	}
}

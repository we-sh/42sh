#include "shell.h"

void	read_history(t_sh *sh, int new, char *filename)
{
	size_t	offset;

	if (filename != NULL)
		env_set(&sh->envp, "HISTFILE", filename);
	offset = new ? sh->termcaps_context.history_initial_size : 0;
	history_load(sh->envp, &sh->termcaps_context.history, &offset);
	sh->termcaps_context.history_initial_size = offset;
	if (filename != NULL)
		env_unset(&sh->envp, "HISTFILE");
}

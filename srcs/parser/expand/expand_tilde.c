#include "shell.h"

int			expand_tilde(t_sh *sh, t_list **argv_list)
{
	t_list	*pos;
	t_argv	*argument;

	pos = (*argv_list)->next;
	if (pos == *argv_list)
		return (ST_OK);
	argument = CONTAINER_OF(pos, t_argv, argv_list);
	return (expand_tilde_through_buffer(sh, &(argument->buffer)));
}

#include "shell.h"

int			globbing_run_parse(t_argv *arg, t_list *list_glob)
{
	t_ctx	*c;

	globbing_load_context(&c, arg->buffer);
	if (!(c->m))
		globbing_add_node_to_list(list_glob, arg);
	else
	{
		if (globbing_run_parse_readir(arg, list_glob, c) == ST_MALLOC)
			return (ST_MALLOC);
	}
	globbing_context_delete(c);
	return (ST_OK);
}

#include "shell.h"

/*
** The purpose of this function is to browse the current argument list, and to
** perform the globbing on each of them.
** The goal is to expand the list of current arguments with the globbing.
*/

int			globbing(t_list **argv_list)
{
	t_list	list_glob;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;

	INIT_LIST_HEAD(&list_glob);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		log_info("proceed globbing on `%s'", arg->buffer);
		if (ft_strchr(arg->buffer, '?') || ft_strchr(arg->buffer, '*') || ft_strchr(arg->buffer, '['))
			globbing_run_parse(arg->buffer, &list_glob);
		else
			globbing_add_node_to_list(&list_glob, arg->buffer);
		// if (arg->buffer)
		// 	free(arg->buffer);
		// if (arg)
		// 	free(arg);
	}
	list_del(*argv_list);
	*argv_list = &list_glob;
	return (ST_OK);
}

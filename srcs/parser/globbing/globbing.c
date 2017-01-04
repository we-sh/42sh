#include "shell.h"

/*
** The purpose of this function is to browse the current argument list, and to
** perform the globbing on each of them.
** The goal is to expand the list of current arguments with the globbing.
*/

int			globbing(t_list **argv_list)
{
	t_list	*list_glob;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;

	if ((list_glob = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (ST_MALLOC);
	INIT_LIST_HEAD(list_glob);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		log_info("proceed globbing on `%s'", arg->buffer);

		if (ft_strchr(arg->buffer, '?') || ft_strchr(arg->buffer, '*') || ft_strchr(arg->buffer, '['))
		{
			globbing_run_parse(arg->buffer, list_glob);
			if (list_is_empty(list_glob))
				globbing_add_node_to_list(list_glob, arg->buffer);
		}
		else
			globbing_add_node_to_list(list_glob, arg->buffer);

		 log_info("Value of arg->buffer", arg->buffer);

		if (arg->buffer)
			free(arg->buffer);

	}
	log_info("before list_del(argv_list)");
	list_del(*argv_list);
	log_info("After list_del(argv_list)");
	globbing_sort_list_glob(&list_glob);
	*argv_list = list_glob;
	return (ST_OK);
}

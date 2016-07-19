#include "shell.h"

/*
** Some stuff to delete.
** How to : add a node to a list.
*/

int	add_node_to_list(t_list *argv_list, char *content)
{
	t_argv		*argument;

	argument = (t_argv *)malloc(sizeof(t_argv));
	if ((argument->buffer = ft_strdup(content)) == NULL)
		return (ST_MALLOC);
	list_push_back(&argument->argv_list, argv_list);
	return (ST_OK);
}

int	globbing_brackets(t_list **argv_list)
{
	t_list	lst_glob;

	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;

	INIT_LIST_HEAD(&lst_glob);

	safe = (*argv_list)->next;
	while ((pos = safe) && safe != *argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);

		log_info("apply globbing on token : `%s'", argument->buffer);

		// stub : it just append 1 word
		add_node_to_list(&lst_glob, argument->buffer);
		// to check if the push front works well :
		//add_node_to_list(&lst_glob, "-l");

		// delete current node
		free(argument->buffer);
		free(argument);
	}
	list_del(*argv_list);
	*argv_list = &lst_glob;
	return (ST_OK);

}

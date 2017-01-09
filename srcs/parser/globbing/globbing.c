#include "shell.h"

static void	s_delete_argv(t_argv **arg)
{
	if (arg && *arg && (*arg)->buffer)
	{
		ft_strdel(&((*arg)->buffer));
		free(*arg);
		arg = NULL;
	}
}
/*
** Check whether a string contains globbing tokens.
*/

static int	s_globbing_is_matching_token(char *arg)
{
	if (!arg)
	{
		return (0);
	}
	if (ft_strchr(arg, '?') || ft_strchr(arg, '*') || ft_strchr(arg, '['))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static void	s_globbing_proceed_on_token(t_list *list_glob, t_argv *arg)
{
	if (!list_glob || !arg || !(arg->buffer))
	{
		return ;
	}
	if (s_globbing_is_matching_token(arg->buffer))
	{
		globbing_run_parse(arg->buffer, list_glob);
		if (list_is_empty(list_glob))
		{
			globbing_add_node_to_list(list_glob, arg->buffer);
		}
		else
			globbing_sort_list_glob(&list_glob);
	}
	else
	{
		globbing_add_node_to_list(list_glob, arg->buffer);
	}
}

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
	{
		return (ST_MALLOC);
	}
	INIT_LIST_HEAD(list_glob);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		s_globbing_proceed_on_token(list_glob, arg);
		s_delete_argv(&arg);
	}
	free(*argv_list);
	*argv_list = list_glob;
	return (ST_OK);
}

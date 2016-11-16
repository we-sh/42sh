#include "shell.h"

/*
** No the beautiful one...
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

/*
** Return 0 if it doesn't match, 1 othewise.
*/

int check_globbing(char *pattern, char *input)
{
	if (*pattern == '?')
	{
		// retrun ( <character> && (0 | 1) )
		return (*input && check_globbing(pattern + 1, input + 1));
	}
	else if (*pattern == '*')
	{
        return (check_globbing(pattern + 1, input) || (*input && check_globbing(pattern, input+1)));
	}
	else
	{
		// return ( 0 | 1 && ( (0 if \0 | 1 otherwise) || ( 0 | 1 ) ) )
        return (*input == *pattern++ && ((*input++ == '\0') || check_globbing(pattern,input)));
	}
}

/*
** This function create the list of what it must be compared
** Doesn't deal with '/'...
*/

int s_globbing_interrogation_parse_argument(char *arg, t_list *list_globbing)
{
	DIR				*dp;
	struct dirent	*ep;

	if ((dp = opendir ("."))) {
		while ((ep = readdir (dp)))
		{
			if (ep->d_name[0] != '.')
			{
				int match = check_globbing(arg, ep->d_name);

				if (match)
					add_node_to_list(list_globbing, ep->d_name);

				log_debug("=> %d -> %s with %s", match, arg, ep->d_name);
			}
		}
		closedir(dp);
	}
	if (list_is_empty(list_globbing))
	{
		log_debug("globbing list is empty (filled with input");
		add_node_to_list(list_globbing, arg);
	}
	return (ST_OK);
}

/*
** 
*/

int	globbing_interrogation(t_list **argv_list)
{
	t_list	list_globbing;

	t_argv	*argument;
	t_list	*pos;
	t_list	*safe;
	int		st;

	INIT_LIST_HEAD(&list_globbing);

	safe = (*argv_list)->next;
	while ((pos = safe) && safe != *argv_list)
	{
		safe = safe->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);

		// beurk
		if (ft_strchr(argument->buffer, '?') || ft_strchr(argument->buffer, '*'))
		{
			log_info("apply globbing on token : `%s'", argument->buffer);
			if ((st = s_globbing_interrogation_parse_argument(argument->buffer, &list_globbing)) != ST_OK)
				return (st);
		}
		else
		{
			add_node_to_list(&list_globbing, argument->buffer);
		}
	}
	// switch lists
	list_del(*argv_list);
	*argv_list = &list_globbing;
	return (ST_OK);
}

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

/*
** extract the context of a pattern
*/

static void	s_globbing_brackets_fill(char *arg, t_list *lst)
{
	char	*context_left;
	char	*context_right;
	char	*pattern;

	char	*ptr;

	pattern = NULL;
	ptr = arg;
	int	i = 0;
	while (1)
	{
		while (i < (int)ft_strlen(arg))
		{
			if (arg[i] == '\\' && arg[i + 1] != '\0' && arg[i + 1] == '[')
				break;
			i++;
		}
		context_left = ft_strsub(arg, 0, i);
		int	j = i;
		while (i < (int)ft_strlen(arg))
		{
			if (arg[i] == '\\' && arg[i + 1] != '\0' && arg[i + 1] == ']')
			{
				pattern = ft_strsub(arg, j, i - j + 2);
				i += 2;
				break;
			}
			i++;
		}
		context_right = ft_strsub(arg, i, ft_strlen(arg) - i);
		log_debug("context left  : %s", context_left);
		log_debug("pattern       : %s", pattern);
		log_debug("context right :%s", context_right);
		break;
	}
	(void)lst;
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
		s_globbing_brackets_fill(argument->buffer, &lst_glob);

		// stub : it just append 1 word
		add_node_to_list(&lst_glob, argument->buffer);
		// to check if the push front works well :
		// add_node_to_list(&lst_glob, "-l");

		// delete current node
		free(argument->buffer);
		free(argument);
	}
	list_del(*argv_list);
	*argv_list = &lst_glob;
	return (ST_OK);

}

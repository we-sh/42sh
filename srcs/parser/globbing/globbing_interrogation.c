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
	/* Context
	 *
	 * if ../../?/?
	 *
	 * 1) left context is ../../
	 *
	 * perform matching on left context + middle
	 * and join the end after
	 *
	 * middle is ?
	 * right context is /?
	 *
	 * 2) ../../x/?
	 *
	 * left context is ../../x
	 * middle is ?
	 * right is null
	 *
	 * peform matching on left context + middle
	 *
	 * while right context is not empty
	 *
	 *
	 */

/*
** no root = 0
** root = 1
*/
char *s_get_left_ctx(char **arg, int is_root)
{
	char *ret = NULL;

	int i = 0;

	if (is_root == 1)
		ret = ft_strdup("/");
	while (arg[i])
	{
		log_trace("%s", arg[i]);
		if (ft_strchr(arg[i], '*') == NULL && ft_strchr(arg[i], '?') == NULL)
		{
			if (ret == NULL)
				ret = ft_strdup(arg[i]);
			else
				ret = ft_strjoin(ret, arg[i]);
			ret = ft_strjoin(ret, "/");
		}
		else
		{
			return (ret);

		}
		log_trace("%s", arg[i]);
		i++;
	}
	return (ret);
}

char *s_get_ctx(char **arg)
{
	int i = 0;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '*'))
			return (ft_strdup(arg[i]));
		if (ft_strchr(arg[i], '?'))
			return (ft_strdup(arg[i]));
		i++;
	}
	return (NULL);
}

char *s_get_right_ctx(char **arg)
{
	char *ret = NULL;

	int i = 0;

	int star_detected = 0;
	while (arg[i])
	{
		if (star_detected == 1)
		{
			if (ret == NULL)
				ret = ft_strdup("/");
			else
				ret = ft_strjoin(ret, "/");
			ret = ft_strjoin(ret, arg[i]);
		}
		if (ft_strchr(arg[i], '*') != NULL || ft_strchr(arg[i], '?') != NULL )
			star_detected = 1;
		i++;
	}
	return (ret);
}

/*
** This function create the list of what it must be compared
** Doesn't deal with '/'...
*/

int s_globbing_interrogation_parse_argument(char *arg, t_list *list_globbing)
{
	DIR				*dp;
	struct dirent	*ep;
	
	log_debug("globbing on %s", arg);


	char **sp = ft_strsplit(arg, '/');

	char *left_ctx;
	if (arg[0] == '/')
		left_ctx = s_get_left_ctx(sp, 1);
	else
		left_ctx = s_get_left_ctx(sp, 0);
	char *ctx = s_get_ctx(sp);
	char *right_ctx = s_get_right_ctx(sp);


	log_debug("left ctx : %s", left_ctx);
	log_debug("ctx      : %s", ctx);
	log_debug("right ctx: %s", right_ctx);

	if (left_ctx == NULL)
		dp = opendir(".");
	else
		dp = opendir(left_ctx);
	
	if (dp != NULL) {
		while ((ep = readdir (dp)))
		{
			if (ep->d_name[0] != '.' || ctx[0] == '.')
			{
				int match = check_globbing(ctx, ep->d_name);

				if (match)
				{
					char *full_match;

					if (left_ctx)
						full_match = ft_strjoin(left_ctx, ep->d_name);
					else
						full_match = ft_strdup(ep->d_name);
					if (right_ctx)
					{
						full_match = ft_strjoin(full_match, right_ctx);
						s_globbing_interrogation_parse_argument(full_match, list_globbing);
					}
					else
						add_node_to_list(list_globbing, full_match);
				}
				log_debug("=> %d -> %s with %s", match, arg, ep->d_name);

			}
		}
		closedir(dp);
	}
	if (list_is_empty(list_globbing))
	{
		log_debug("globbing list is empty (filled with input %s)", arg);
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

#include "shell.h"

/*
** Add a node composed of a string at the end of the list in argument.
*/

static int	s_add_node_to_list(t_list *argv_list, char *content)
{
	t_argv		*argument;

	if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
		return (ST_MALLOC);
	if ((argument->buffer = ft_strdup(content)) == NULL)
		return (ST_MALLOC);
	list_push_back(&argument->argv_list, argv_list);
	return (ST_OK);
}

/*
** Return 0 if it doesn't match, 1 othewise.
** This function checks if the input string matches with the pattern provided in
** argument.
** It returns 0 if it doesn't match, 1 otherwise.
*/

static int	check_globbing(char *pattern, char *input)
{
	if (*pattern == '?')
	{
		return (*input && check_globbing(pattern + 1, input + 1));
	}
	else if (*pattern == '*')
	{
		return (check_globbing(pattern + 1, input) ||
				(*input && check_globbing(pattern, input + 1)));
	}
	else
	{
		return (*input == *pattern++ && ((*input++ == '\0') ||
					check_globbing(pattern, input)));
	}
}

/*
** This function create the list of what it must be compared
** Doesn't deal with '/'...
*/

static int	s_globbing_interrogation_parse_argument(char *arg,
		t_list *list_globbing)
{
	t_ctx			*ctx;
	DIR				*dp;
	struct dirent	*ep;
	char			*full_match;

	globbing_load_context(&ctx, arg);
	log_debug("left   ctx: ", ctx->left);
	log_debug("middle ctx: ", ctx->middle);
	log_debug("right  ctx: ", ctx->right);
	if (ctx->left == NULL)
		dp = opendir(".");
	else
		dp = opendir(ctx->left);
	if (dp != NULL)
	{
		while ((ep = readdir(dp)))
		{
			if (ep->d_name[0] != '.' || ctx->middle[0] == '.')
			{
				if (check_globbing(ctx->middle, ep->d_name))
				{
					if (ctx->left)
						full_match = ft_strjoin(ctx->left, ep->d_name);
					else
						full_match = ft_strdup(ep->d_name);
					if (ctx->right)
					{
						full_match = ft_strjoin(full_match, ctx->right);
						s_globbing_interrogation_parse_argument(full_match,
								list_globbing);
					}
					else
						s_add_node_to_list(list_globbing, full_match);
				}
			}
		}
		closedir(dp);
	}
	if (list_is_empty(list_globbing))
	{
		log_debug("globbing list is empty (filled with input %s)", arg);
		s_add_node_to_list(list_globbing, arg);
	}
	return (ST_OK);
}

/*
** The purpose of this function is to browse the current argument list, and to
** perform the globbing on each of them.
** The goal is to expand the list of current arguments with the globbing.
*/

int	globbing_interrogation(t_list **argv_list)
{
	t_list	list_globbing;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;
	int		st;

	INIT_LIST_HEAD(&list_globbing);
	safe = (*argv_list)->next;
	while ((pos = safe) && safe != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		if (ft_strchr(arg->buffer, '?') || ft_strchr(arg->buffer, '*'))
		{
			log_info("apply globbing on token : `%s'", arg->buffer);
			if ((st = s_globbing_interrogation_parse_argument(
							arg->buffer, &list_globbing)) != ST_OK)
				return (st);
		}
		else
			s_add_node_to_list(&list_globbing, arg->buffer);
	}
	list_del(*argv_list);
	*argv_list = &list_globbing;
	return (ST_OK);
}

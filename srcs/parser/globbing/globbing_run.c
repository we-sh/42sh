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
	if (!pattern || !input)
		return (0);
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
*/

static int	s_globbing_run_parse(char *arg, t_list *list_glob)
{
	t_ctx			*ctx;
	DIR				*dp;
	struct dirent	*ep;
	char			*full_match;
	char			*ptr;

	full_match = NULL;
	globbing_load_context(&ctx, arg);
	dp = (!(ctx->left)) ? opendir(".") : opendir(ctx->left);
	if (dp != NULL)
	{
		while ((ep = readdir(dp)))
		{
			if (ep->d_name[0] != '.' || (ctx->middle && ctx->middle[0] == '.'))
			{
				if (check_globbing(ctx->middle, ep->d_name))
				{
					full_match = (ctx->left)
						? ft_strjoin(ctx->left, ep->d_name)
						: ft_strdup(ep->d_name);
					if (ctx->right)
					{
						ptr = full_match;
						full_match = ft_strjoin(ptr, ctx->right);
						ft_strdel(&ptr);
						s_globbing_run_parse(full_match, list_glob);
					}
					else
						s_add_node_to_list(list_glob, full_match);
					ft_strdel(&full_match);
				}
			}
		}
		closedir(dp);
	}
	if (list_is_empty(list_glob) && dp != NULL)
		s_add_node_to_list(list_glob, arg);
	if (ctx)
	{
		if (ctx->left)
			free(ctx->left);
		if (ctx->middle)
			free(ctx->middle);
		if (ctx->right)
			free(ctx->right);
		free(ctx);
	}
	return (ST_OK);
}

/*
** The purpose of this function is to browse the current argument list, and to
** perform the globbing on each of them.
** The goal is to expand the list of current arguments with the globbing.
*/

int			globbing_run(t_list **argv_list)
{
	t_list	list_glob;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;
	int		st;

	INIT_LIST_HEAD(&list_glob);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		if (ft_strchr(arg->buffer, '?') || ft_strchr(arg->buffer, '*'))
		{
			log_info("apply globbing on token : `%s'", arg->buffer);
			if ((st = s_globbing_run_parse(arg->buffer, &list_glob)) != ST_OK)
				return (st);
		}
		else
			s_add_node_to_list(&list_glob, arg->buffer);
		if (arg && arg->buffer)
		{
			free(arg->buffer);
			free(arg);
		}
	}
	list_del(*argv_list);
	*argv_list = &list_glob;
	return (ST_OK);
}

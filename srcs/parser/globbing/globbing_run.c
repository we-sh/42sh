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

static char	*s_join_free(char *s1, char *s2)
{
	char *ret;

	ret = NULL;
	if (s1 && s2)
	{
		ret = ft_strjoin(s1, s2);
		ft_strdel(&s1);
	}
	return (ret);
}

typedef struct s_mylist
{
	struct s_mylist		*next;
	char				*content;
}					t_mylist;

void globbing_bracket(t_mylist **list, char *input)
{
	log_debug("\t\tproduce bracket list expansion on `%s'", input);

	if (*list == NULL)
	{
		*list = ft_memalloc(sizeof(t_mylist));
	}
	(*list)->content = ft_strdup(input);
}

/*
** This function create the list of what it must be compared
*/

static void	s_globbing_run_parse(char *arg, t_list *list_glob)
{
	t_ctx			*c;
	DIR				*dp;
	struct dirent	*e;
	char			*m;

	t_mylist *list = NULL;

	globbing_load_context(&c, arg);
	log_debug("left context   : `%s'", c->l);
	log_debug("middle context : `%s'", c->m);
	log_debug("right context  : `%s'", c->r);
	if ((dp = (!(c->l)) ? opendir(".") : opendir(c->l)))
	{
		while ((e = readdir(dp)))
		{
			if (e->d_name[0] != '.' || (c->m && c->m[0] == '.'))
			{		
				log_debug("\tperforming globbing on (middle context) `%s' with (file name) `%s'", c->m, e->d_name);
				globbing_bracket(&list, c->m);
				while (list)
				{
					if (check_globbing(list->content, e->d_name))
					{
						m = (c->l) ? ft_strjoin(c->l, e->d_name) : ft_strdup(e->d_name);
						log_info("\tperforming globbing on (middle context) `%s' with (file name) `%s' => produce `%s'", c->m, e->d_name, m);
						c->r ? s_globbing_run_parse(m = s_join_free(m, c->r), list_glob) : s_add_node_to_list(list_glob, m);
						ft_strdel(&m);
					}
					ft_strdel(&(list->content));
					list = list->next;
				}
			}
		}
		closedir(dp);
	}
	//if (list_is_empty(list_glob) && dp != NULL && (ft_strchr(arg, '?') || ft_strchr(arg, '*')))
	if (list_is_empty(list_glob) && (ft_strchr(arg, '?') || ft_strchr(arg, '*')))
		s_add_node_to_list(list_glob, arg);
	globbing_context_delete(c);
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

	INIT_LIST_HEAD(&list_glob);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		log_info("proceed globbing on `%s'", arg->buffer);
		if (ft_strchr(arg->buffer, '?') || ft_strchr(arg->buffer, '*') || ft_strchr(arg->buffer, '['))
			s_globbing_run_parse(arg->buffer, &list_glob);
		else
			s_add_node_to_list(&list_glob, arg->buffer);
		if (arg->buffer)
			free(arg->buffer);
		if (arg)
			free(arg);
	}
	list_del(*argv_list);
	*argv_list = &list_glob;
	return (ST_OK);
}
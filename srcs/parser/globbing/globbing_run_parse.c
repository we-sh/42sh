#include "shell.h"

static char		*s_join_free(char *s1, char *s2)
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

/*
** Delete a node list and return the next node.
*/

static t_mylist	*s_mylist_del_safe(t_mylist **list)
{
	t_mylist	*ret;

	ret = NULL;
	if (list && *list && (*list)->content)
	{
		ret = (*list)->next;
		ft_strdel(&((*list)->content));
		free(*list);
		list = NULL;
	}
	return (ret);
}

static void		s_apply_globbing(t_list *list_glob, t_ctx *c)
{
	char	*m;

	if (c->l)
		m = ft_strjoin(c->l, c->c_file->d_name);
	else
		m = ft_strdup(c->c_file->d_name);
	if (c->r)
		globbing_run_parse(m = s_join_free(m, c->r), list_glob);
	else
		globbing_add_node_to_list(list_glob, m);
	ft_strdel(&m);
}

static void		s_globbing_run_parse_arg(t_list *list_glob, t_ctx *c,
		char *arg, int *i)
{
	t_mylist		*list;
	int				ret;

	list = NULL;
	if (globbing_bracket(&list, c->m, c->c_file->d_name) == -1)
	{
		globbing_add_node_to_list(list_glob, arg);
		return ;
	}
	ret = 0;
	while (list)
	{
		if ((ret = globbing_check(list->content, c->c_file->d_name)) > 0)
		{
			s_apply_globbing(list_glob, c);
			*i = *i + 1;
		}
		else if (ret == -1)
		{
			globbing_add_node_to_list(list_glob, arg);
			return ;
		}
		list = s_mylist_del_safe(&list);
	}
}

/*
** This function create the list of what it must be compared
*/

void			globbing_run_parse(char *arg, t_list *list_glob)
{
	t_ctx			*c;
	DIR				*dp;
	int				i;

	i = 0;
	globbing_load_context(&c, arg);
	if (!(c->m))
		globbing_add_node_to_list(list_glob, arg);
	else
	{
		if ((dp = (!(c->l)) ? opendir(".") : opendir(c->l)))
		{
			while ((c->c_file = readdir(dp)))
			{
				if (c->c_file->d_name[0] != '.' || (c->m && c->m[0] == '.'))
					s_globbing_run_parse_arg(list_glob, c, arg, &i);
			}
			if (i <= 0)
				globbing_add_node_to_list(list_glob, arg);
			closedir(dp);
		}
	}
	globbing_context_delete(c);
}

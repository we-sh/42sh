#include "shell.h"

/*
** Return 0 if it doesn't match, 1 othewise.
** This function checks if the input string matches with the pattern provided in
** argument.
** It returns 0 if it doesn't match, 1 otherwise.
*/

int	check_globbing(char *pattern, char *input)
{
	char *is_valid;

	is_valid = 0;
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

/*
** Delete a node list and return the next node.
*/

static t_mylist *s_mylist_del_safe(t_mylist **list)
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

/*
** This function create the list of what it must be compared
*/

void				globbing_run_parse(char *arg, t_list *list_glob)
{
	t_ctx			*c;
	DIR				*dp;
	struct dirent	*e;
	int				i;
	int				ret;
	char			*m;
	t_mylist		*list;

	i = 0;
	list = NULL;
	globbing_load_context(&c, arg);
	if (!(c->m))
		globbing_add_node_to_list(list_glob, arg);
	else
	{
		if ((dp = (!(c->l)) ? opendir(".") : opendir(c->l)))
		{
			while ((e = readdir(dp)))
			{
				if (e->d_name[0] != '.' || (c->m && c->m[0] == '.'))
				{
					if (globbing_bracket(&list, c->m, e->d_name) == -1)
					{
						globbing_add_node_to_list(list_glob, arg);
						return ;
					}
					ret = 0;
					while (list)
					{
						if ((ret = check_globbing(list->content, e->d_name)) > 0)
						{
							if (c->l)
								m = ft_strjoin(c->l, e->d_name);
							else
								m = ft_strdup(e->d_name);
							if (c->r)
								globbing_run_parse(m = s_join_free(m, c->r), list_glob);
							else
								globbing_add_node_to_list(list_glob, m);
							ft_strdel(&m);
							i += 1;
						}
						else if (ret == -1)
						{
							globbing_add_node_to_list(list_glob, arg);
							return ;
						}
						list = s_mylist_del_safe(&list);
					}
				}
			}
			if (i <= 0)
				globbing_add_node_to_list(list_glob, arg);
			closedir(dp);
		}
	}
	globbing_context_delete(c);
}

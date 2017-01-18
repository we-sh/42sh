#include "shell.h"

static char		*s_join_free(char *s1, char *s2)
{
	char *ret;

	ret = NULL;
	if (s1 && s2)
	{
		if ((ret = ft_strjoin(s1, s2)) == NULL)
			return (NULL);
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

static int		s_apply_globbing(t_list *list_glob, t_ctx *c, t_argv *arg)
{
	char	*m;

	if (c->l)
	{
		if ((m = ft_strjoin(c->l, c->c_file->d_name)) == NULL)
			return (ST_MALLOC);
	}
	else
	{
		if ((m = ft_strdup(c->c_file->d_name)) == NULL)
			return (ST_MALLOC);
	}
	if (c->r)
	{
		if ((m = s_join_free(m, c->r)) == NULL)
			return (ST_MALLOC);
		free(arg->buffer);
		arg->buffer = m;
		globbing_run_parse(arg, list_glob);
	}
	else
	{
		log_success("Go inside add_node_alpha:%s ", m);
		globbing_add_node_alpha_to_list(list_glob, m);
	}
	ft_strdel(&m);
	return (ST_OK);
}

static int		s_globbing_run_parse_arg(t_list *list_glob, t_ctx *c,
		t_argv *arg, int *i)
{
	t_mylist		*list;
	int				ret;

	list = NULL;
	log_debug("inside s_globbing_run_parse_arg c->c_file->d_name:%s ",c->c_file->d_name);
	if (!(ret = 0) && globbing_bracket(&list, c->m, c->c_file->d_name) == -1)
	{
		log_success("Add arg in run parse if glob brack -q:%s ", arg);
		globbing_add_node_to_list(list_glob, arg->buffer);
		return (ST_OK);
	}
	log_debug("Before while list");
	while (list)
	{
		log_warn("list->content:%s ", list->content);
		if ((ret = globbing_check(list->content, c->c_file->d_name)) > 0)
		{
			if ((s_apply_globbing(list_glob, c, arg)) == ST_MALLOC)
				return (ST_MALLOC);
			*i = *i + 1;
		}
		else if (ret == -1)
		{
			log_success("Add arg in run parse if ret -1:%s ", arg->buffer);
			globbing_add_node_to_list(list_glob, arg->buffer);
			return (ST_OK);
		}
		list = s_mylist_del_safe(&list);
	}
	log_error("OUT");
	return (ST_OK);
}

/*
** This function create the list of what it must be compared
*/

int					globbing_run_parse(t_argv *arg, t_list *list_glob)
{
	t_ctx			*c;
	DIR				*dp;
	int				i;

	log_info("inside globbing_run_parse value of arg->content:%s", arg->buffer);
	globbing_load_context(&c, arg->buffer);
	if (!(i = 0) && !(c->m))
	{
		log_success("add node inside run parse:%s", arg->buffer);		
		globbing_add_node_to_list(list_glob, arg->buffer);
	}
	else
	{
		if ((dp = (!(c->l)) ? opendir(".") : opendir(c->l)))
		{
			while ((c->c_file = readdir(dp)))
			{
				if (c->c_file->d_name[0] != '.' || (c->m && c->m[0] == '.'))
				{
					if ((s_globbing_run_parse_arg(list_glob, c, arg, &i)) == ST_MALLOC)
						return (ST_MALLOC);
				}
			}
			if (i <= 0)
			{
				log_success("add node inside run parse:%s", arg->buffer);
				globbing_add_node_to_list(list_glob, arg->buffer);
			}
			closedir(dp);
		}
	}
	globbing_context_delete(c);
	return (ST_OK);
}

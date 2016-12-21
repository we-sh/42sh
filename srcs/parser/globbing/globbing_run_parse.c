#include "shell.h"

/*
** Return 0 if it doesn't match, 1 othewise.
** This function checks if the input string matches with the pattern provided in
** argument.
** It returns 0 if it doesn't match, 1 otherwise.
*/

static int	s_check_globbing(char *pattern, char *input)
{
	if (!pattern || !input)
		return (0);
	log_error("Pattern:%c, input:%c",*pattern, *input);
	if (ft_strchr(pattern,'[') || ft_strchr(pattern, ']'))
	{
		log_error("if [ or ] are still a part of the string, an error occured");
		return (-1);
	}
	if (*pattern == '?')
	{
		return (*input && s_check_globbing(pattern + 1, input + 1));
	}
	else if (*pattern == '*')
	{
		return (s_check_globbing(pattern + 1, input) ||
				(*input && s_check_globbing(pattern, input + 1)));
	}
	else
	{
		return (*input == *pattern++ && ((*input++ == '\0') ||
					s_check_globbing(pattern, input)));
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
** This function create the list of what it must be compared
*/

void 				globbing_run_parse(char *arg, t_list *list_glob)
{
	t_ctx     *c;
	DIR       *dp;
	struct dirent *e;
	int i=0;//debug

	t_mylist *list;

	list = NULL;
	globbing_load_context(&c, arg);
	log_debug("left context   : `%s'", c->l);
	log_debug("middle context : `%s'", c->m);
	log_debug("right context  : `%s'", c->r);
	if ((dp = (!(c->l)) ? opendir(".") : opendir(c->l)))
	{
		log_info("Before while readdir");
		while ((e = readdir(dp)))
		{
			//log_success("turn  : `%d' -> %s", i,e->d_name);
			if (e->d_name[0] != '.' || (c->m && c->m[0] == '.'))
			{
				log_debug("\tWHILE readit(dp) performing globbing on (middle context) `%s' \n\t\t\t\twith (file name) `%s'", c->m, e->d_name);
				globbing_bracket(&list, c->m);
				//s_iter_on_list(list, c, list_glob, e, &i, arg);	
					int ret;
					char      *m;

					ret = 0;
					while (list)
					{
						log_debug("after globbing_bracket list->content:%s", list->content);
						log_debug("after globbing_bracket e->d_name:%s", e->d_name);
						if ((ret = s_check_globbing(list->content, e->d_name)) > 0)
						{
							log_debug("Value of RET:%d", ret);
							if (c->l)
								m = ft_strjoin(c->l, e->d_name);
							else
								m = ft_strdup(e->d_name);

							log_info("\t2performing globbing on (middle context) `%s' \n\t\t\t\twith (file name) `%s' => produce `%s'", c->m, e->d_name, m);
							log_info("c->l:%s", c->l);
							log_info("c->m:%s", c->m);
							log_info("c->r:%s", c->r);
							if (c->r)
							 globbing_run_parse(m = s_join_free(m, c->r), list_glob);
							else
								globbing_add_node_to_list(list_glob, m);
							ft_strdel(&m);
							i += 1;//debug
						}
						else if (ret == -1)// ret of check-globing equal -1 so we didn't replace bracket and return input
						{
								log_debug("Value of RET:%d", ret);
								globbing_add_node_to_list(list_glob, arg);
								return ;
						}
						log_debug("Value of RET:%d", ret);
						ft_strdel(&(list->content));
						list = list->next;
					}
			}
		}
		if (i ==0)
		{
			log_info("RET=%d..et a toujours ete 0");
			globbing_add_node_to_list(list_glob, c->m);
		}
		closedir(dp);
	}
	//if (list_is_empty(list_glob) && dp != NULL && (ft_strchr(arg, '?') || ft_strchr(arg, '*')))
	if (list_is_empty(list_glob) && (ft_strchr(arg, '?') || ft_strchr(arg, '*')))
		globbing_add_node_to_list(list_glob, arg);
	globbing_context_delete(c);
}

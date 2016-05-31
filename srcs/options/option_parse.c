#include "shell.h"

/*
** This function may parse options.
**
** It considers:
** - multiple options with single characters (e.g. `rm -rf`, `ls -lRA`)
** - single options with multiple characters (e.g. `--unset`)
** - value that may follow the option (e.g. `-u PATH`)
** - delimiter of end of options `--`
**
** For more information about POSIX options:
** http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html
*/

static int			s_value_is_valid(t_option const **available_opt,
						size_t opt, char *value)
{
	if (available_opt[opt]->has_value == 1)
	{
		if (value == NULL)
			return (-ST_EINVAL);
		if (available_opt[opt]->value_is_numeric == 1
			&& ft_strisnumeric(value) == 0)
			return (-ST_EINVAL);
		if (available_opt[opt]->value_is_alnum == 1
			&& ft_strisalnum(value) == 0)
			return (-ST_EINVAL);
		if (available_opt[opt]->value_is_indexof != NULL
			&& ft_array_indexof(available_opt[opt]->value_is_indexof, value) == -1)
			return (-ST_EINVAL);
	}
	return (opt);
}

static int			s_is_valid(t_option const **available_opt,
						char **argv, size_t i, size_t is_single_char)
{
	size_t			k;

	k = 0;
	while (available_opt[k])
	{
		if (is_single_char > 0 && available_opt[k]->is_single_char == 1
			&& argv[i][is_single_char] == available_opt[k]->name[0])
		{
			if (available_opt[k]->has_value == 1
				&& (argv[i][is_single_char + 1] != '\0' || is_single_char > 1))
				return (-ST_EINVAL);
			return (s_value_is_valid(available_opt, k, argv[i + 1]));
		}
		if (is_single_char == 0
			&& ft_strcmp(argv[i] + 2, available_opt[k]->name) == 0)
			return (s_value_is_valid(available_opt, k, argv[i + 1]));
		k++;
	}
	return (-ST_EINVAL);
}

static int			s_single(t_list *list_head,
						t_option const **available_opt,
						char ***argv, size_t i)
{
	size_t			k;
	int				opt;
	t_list			*option_node;

	k = 1;
	while ((*argv)[i][k])
	{
		log_debug("parsing single character option %c", (*argv)[i][k]);
		if ((opt = s_is_valid(available_opt, *argv, i, k)) < ST_OK)
			return (-opt);
		if ((option_node = list_node__option_alloc(available_opt[opt], *argv, i)) == NULL)
			return (ST_MALLOC);
		list_push_back(option_node, list_head);
		k++;
	}
	ft_array_pop(argv, i, 1);
	if (k == 2 && available_opt[opt]->has_value == 1)
		ft_array_pop(argv, i, 1);
	return (ST_OK);
}

static int			s_multi(t_list *list_head,
						t_option const **available_opt,
						char ***argv, size_t i)
{
	int				opt;
	t_list			*option_node;

	log_debug("parsing multi character option %s", (*argv)[i] + 2);
	if ((opt = s_is_valid(available_opt, *argv, i, 0)) < ST_OK)
		return (-opt);
	if ((option_node = list_node__option_alloc(available_opt[opt], *argv, i)) == NULL)
		return (ST_MALLOC);
	list_push_back(option_node, list_head);
	ft_array_pop(argv, i, 1);
	if (available_opt[opt]->has_value == 1)
		ft_array_pop(argv, i, 1);
	return (ST_OK);
}

int					option_parse(t_list *list_head,
						t_option const **available_opt,
						char ***argv, size_t start)
{
	size_t		i;
	int			ret;

	i = start;
	INIT_LIST_HEAD(list_head);
	while ((*argv)[i])
	{
		if ((*argv)[i][0] != '-' || ((*argv)[i][0] == '-' && (*argv)[i][1] == '\0')
			|| ft_strcmp((*argv)[i], "--") == 0)
			break ;
		if ((*argv)[i][0] == '-' && (*argv)[i][1] != '-')
		{
			if ((ret = s_single(list_head, available_opt, argv, i)) != ST_OK)
				return (ret);
			i -= 1;
		}
		else if ((*argv)[i][0] == '-' && (*argv)[i][1] == '-')
		{
			if ((ret = s_multi(list_head, available_opt, argv, i)) != ST_OK)
				return (ret);
			i -= 1;
		}
		i++;
	}
	return (ST_OK);
}

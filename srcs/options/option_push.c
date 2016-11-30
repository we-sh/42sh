#include "shell.h"

static t_option	*s_get_option(t_list *list_head, int option_index)
{
	t_list		*opt_pos;
	t_option	*opt;

	opt_pos = list_head;
	while ((opt_pos = opt_pos->next) && opt_pos != list_head)
	{
		opt = CONTAINER_OF(opt_pos, t_option, list_option);
		if (opt->index == option_index)
			return (opt);
	}
	return (NULL);
}

static int		s_push_value(char ***values, char *value)
{
	if (*values == NULL)
	{
		if ((*values = malloc(sizeof(char **) * 1)) == NULL)
			return (ST_MALLOC);
		(*values)[0] = NULL;
	}
	if (ft_array_push_back(values, value) < 0)
		return (ST_MALLOC);
	return (ST_OK);
}

int				option_push(t_list *list_head, t_option const *option_ref,
					char **argv, size_t i)
{
	t_option	*option;

	if ((option = s_get_option(list_head, option_ref->index)) == NULL)
	{
		if ((option = malloc(sizeof(t_option))) == NULL)
			return (ST_MALLOC);
		list_push_back(&option->list_option, list_head);
		option->index = option_ref->index;
		option->name = option_ref->name;
		option->is_single_char = option_ref->is_single_char;
		option->has_value = option_ref->has_value;
		option->has_multiple_values = option_ref->has_multiple_values;
		option->value_is_numeric = option_ref->value_is_numeric;
		option->value_is_alnum = option_ref->value_is_alnum;
		option->value = NULL;
		option->values = NULL;
	}
	if (option_ref->has_multiple_values == 1)
		return (s_push_value(&option->values, argv[i + 1]));
	if (option_ref->has_value == 1 && option->value == NULL)
		if ((option->value = ft_strdup(argv[i + 1])) == NULL)
			return (ST_MALLOC);
	return (ST_OK);
}

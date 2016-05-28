#include "shell.h"

t_list			*list_node__option_alloc(t_option const *option_ref,
					char **argv, size_t i)
{
	t_option	*option;

	if ((option = malloc(sizeof(t_option))) == NULL)
		return (NULL);
	option->name = option_ref->name;
	option->is_single_char = option_ref->is_single_char;
	option->has_value = option_ref->has_value;
	option->value_is_numeric_only = option_ref->value_is_numeric_only;
	option->value_is_alnum_only = option_ref->value_is_alnum_only;
	option->value = NULL;
	if (option_ref->has_value == 1)
		if ((option->value = ft_strdup(argv[i + 1])) == NULL)
			return (NULL);
	return (&option->list_option);
}

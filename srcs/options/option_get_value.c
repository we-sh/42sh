#include "shell.h"

char	*option_get_value(t_list *list_option_head, int option_index)
{
	t_list		*opt_pos;
	t_option	*opt;

	LIST_FOREACH(list_option_head, opt_pos)
	{
		opt = CONTAINER_OF(opt_pos, t_option, list_option);
		if (opt->index == option_index)
			return (opt->value);
	}
	return (NULL);
}

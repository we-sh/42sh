#include "shell.h"

int	option_is_set(t_list *list_option_head, int option_index)
{
	t_list		*opt_pos;
	t_option	*opt;

	LIST_FOREACH(list_option_head, opt_pos)
	{
		opt = CONTAINER_OF(opt_pos, t_option, list_option);
		log_debug("%s %d %d", opt->name, opt->index, ST_BLTIN_JOBS_OPT_L);
		if (opt->index == option_index)
			return (1);
	}
	return (0);
}

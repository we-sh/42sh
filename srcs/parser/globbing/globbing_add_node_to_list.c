#include "shell.h"

static t_argv	*s_set_arg(char *content, t_argv *arg_base)
{
	t_argv		*argument;

	if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
		return (NULL);
	if ((argument->buffer = ft_strdup(content)) == NULL)
		return (NULL);
	argument->pos = arg_base->pos;
	argument->is_null = 0;
	return (argument);
}

int				globbing_add_node_to_list(t_list *argv_list, t_argv *arg_base)
{
	t_argv		*argument;
	t_argv		*arg;
	t_list		*pos;
	t_list		*safe;

	if ((argument = s_set_arg(arg_base->buffer, arg_base)) == NULL)
		return (ST_MALLOC);
	safe = argv_list->next;
	while ((pos = safe) && pos != argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		arg->pos = arg_base->pos;
		if (ft_strcmp(arg->buffer, arg_base->buffer) == 0)
		{
			free(argument->buffer);
			free(argument);
			return (ST_OK);
		}
	}
	list_push_back(&argument->argv_list, argv_list);
	return (ST_OK);
}

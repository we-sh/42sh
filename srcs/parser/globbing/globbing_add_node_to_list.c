#include "shell.h"

static t_argv *s_set_arg(char *content)
{
	t_argv    *argument;

	if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
		return (NULL);
	if ((argument->buffer = ft_strdup(content)) == NULL)
		return (NULL);
	argument->is_null = 0;
	return (argument);
}

static int s_add_node_loop(t_list **safe, t_list *argv_list, t_argv *argument, t_argv *arg, int *index, int *ret)
{
	t_list		*pos;

	while ((pos = *safe) &&  pos != argv_list && (*ret = ft_strcmp(argument->buffer, arg->buffer)) > 0)
	{
		*safe = (*safe)->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		if ((*ret = ft_strcmp(argument->buffer, arg->buffer)) < 0)
		{
			*index += 1;
			list_insert(&argument->argv_list, argv_list, *index);
			return (ST_DONE);
		}
		else if (*ret == 0)
		{
			*index += 1;
			free(arg->buffer);
			free(arg);
			return (ST_DONE);
		}
		*ret = 1;
		*index += 1;
	}
	return (ST_OK);
}

int				globbing_add_node_alpha_to_list(t_list *argv_list, char *content)
{
	t_argv		*argument;
	t_argv		*arg;
	t_list		*pos;
	t_list		*safe;
	int			index;
	int			ret;

	index = 0;
	ret = 0;
	argument = s_set_arg(content);
	safe = argv_list->next;
	while ((pos = safe) && pos != argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		if ((ret =ft_strcmp(content, arg->buffer)) < 0)
		{
			list_insert(&argument->argv_list, argv_list, index);
			return (ST_OK) ;
		}
		if ((s_add_node_loop(&safe, argv_list, argument, arg, &index, &ret)) == ST_DONE)
			return (ST_OK);
		if (ret != 0)
			index += 1;
	}
	list_insert(&argument->argv_list, argv_list, index);
	return (ST_OK);
}

int			globbing_add_node_to_list(t_list *argv_list, char *content)
{
	t_argv	*argument;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;

	if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
		return (ST_MALLOC);
	if ((argument->buffer = ft_strdup(content)) == NULL)
		return (ST_MALLOC);
	argument->is_null = 0;
	safe = argv_list->next;
	while ((pos = safe) && pos != argv_list)
	{
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		if (ft_strcmp(arg->buffer, content) == 0)
		{
			free(argument->buffer);
			free(argument);
			return (ST_OK);
		}
	}
	list_push_back(&argument->argv_list, argv_list);
	return (ST_OK);
}


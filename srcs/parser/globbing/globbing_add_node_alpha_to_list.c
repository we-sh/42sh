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

static int		s_add_node_loop(t_utils *ctn,
									t_list *list_glob,
									int *index,
									int *ret)
{
	t_list		*pos;

	while ((pos = ctn->safe) && pos != list_glob &&
		(*ret = ft_strcmp(ctn->argument->buffer, ctn->arg->buffer)) > 0)
	{
		ctn->safe = ctn->safe->next;
		ctn->arg = CONTAINER_OF(pos, t_argv, argv_list);
		if ((*ret = ft_strcmp(ctn->argument->buffer, ctn->arg->buffer)) < 0)
		{
			*index += 1;
			list_insert(&ctn->argument->argv_list, list_glob, *index);
			return (ST_DONE);
		}
		else if (*ret == 0)
		{
			*index += 1;
			free(ctn->arg->buffer);
			free(ctn->arg);
			return (ST_DONE);
		}
		*ret = 1;
		*index += 1;
	}
	return (ST_OK);
}

static t_utils	*s_set_container(t_list *list_glob,
									char *content,
									t_argv *arg_base)
{
	t_utils		*container;

	if ((container = (t_utils *)malloc(sizeof(t_utils))) == NULL)
		return (NULL);
	if ((container->argument = s_set_arg(content, arg_base)) == NULL)
		return (NULL);
	container->safe = list_glob->next;
	return (container);
}

static int		s_insert_free_and_return(t_utils *container,
											t_list *list_glob,
											int index)
{
	list_insert(&container->argument->argv_list, list_glob, index);
	free(container);
	return (ST_OK);
}

int				globbing_add_node_alpha_to_list(t_list *list_glob,
													char *content,
													t_argv *arg_base)
{
	t_utils		*container;
	int			index;
	int			ret;

	index = 0;
	if ((container = s_set_container(list_glob, content, arg_base)) == NULL)
		return (ST_MALLOC);
	while ((container->pos = container->safe) && container->pos != list_glob)
	{
		container->safe = container->safe->next;
		container->arg = CONTAINER_OF(container->pos, t_argv, argv_list);
		ret = ft_strcmp(content, container->arg->buffer);
		if ((container->arg->pos == arg_base->pos) && ret < 0)
			return (s_insert_free_and_return(container, list_glob, index));
		if ((s_add_node_loop(container, list_glob, &index, &ret)) == ST_DONE)
		{
			free(container);
			return (ST_OK);
		}
		if (ret != 0)
			index += 1;
	}
	return (s_insert_free_and_return(container, list_glob, index));
}

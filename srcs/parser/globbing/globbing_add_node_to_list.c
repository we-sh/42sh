#include "shell.h"

int    globbing_add_node_alpha_to_list(t_list *list_glob, char *content, t_argv *arg_base)
{
  t_argv    *argument;
  t_argv    *arg;
  t_list    *pos;
  t_list    *safe;
  int     index=0;
  int     ret=0;

  if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
	return (ST_MALLOC);
  if ((argument->buffer = ft_strdup(content)) == NULL)
	return (ST_MALLOC);
  argument->is_null = 0;
  argument->pos = arg_base->pos;
  safe = list_glob->next;
log_error("Valeur of arg_base->pos:%d, arg_base->buffer:%s ", arg_base->pos, arg_base->buffer);  
  while ((pos = safe) && pos != list_glob)
  {
	safe = safe->next;
	arg = CONTAINER_OF(pos, t_argv, argv_list);
	ret = ft_strcmp(content, arg->buffer);
	log_error("Valeur of arg_base->pos:%d, arg_base->buffer:%s ", arg->pos, arg->buffer);  
	if ((arg->pos == arg_base->pos) && (ret = ft_strcmp(content, arg->buffer)) < 0)
	{
		list_insert(&argument->argv_list, list_glob, index);
		return (ST_OK) ;
	}
	while ((pos = safe) &&  pos != list_glob && (ret = ft_strcmp(content, arg->buffer)) > 0)
	{
	  safe = safe->next;
	  arg = CONTAINER_OF(pos, t_argv, argv_list);
	  if ((ret = ft_strcmp(content, arg->buffer)) < 0)
	  {
		index++;
		log_success("insert at index:%d :%d ", index, ret);
		list_insert(&argument->argv_list, list_glob, index);
		return (ST_OK) ;
	  }
	  else if (ret == 0)
	  {
		index++;
		free(arg->buffer);
		free(arg);
		return (ST_OK) ;
	  }
	  ret = 1;
	  index++;
	}
	if (ret != 0)
		index++;
  }
	log_success("insert at index:%d :%d ", index, ret);
  list_insert(&argument->argv_list, list_glob, index);
  return (ST_OK);
}


int			globbing_add_node_to_list(t_list *argv_list, t_argv *arg_base)
{
	t_argv	*argument;
	t_argv	*arg;
	t_list	*pos;
	t_list	*safe;

	if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
		return (ST_MALLOC);
	if ((argument->buffer = ft_strdup(arg_base->buffer)) == NULL)
		return (ST_MALLOC);
	argument->is_null = 0;
	argument->pos = arg_base->pos;
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

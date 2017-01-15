#include "shell.h"

int    globbing_add_node_alpha_to_list(t_list *argv_list, char *content)
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
  safe = argv_list->next;
  while ((pos = safe) && pos != argv_list)
  {
	safe = safe->next;
	arg = CONTAINER_OF(pos, t_argv, argv_list);
	  log_success("value of content:%s, arg->buffer:%s",content ,arg->buffer);
	while ((pos = safe) &&  pos != argv_list && ((ret = ft_strcmp(content, arg->buffer)) > 0))
	{
	  safe = safe->next;
	  arg = CONTAINER_OF(pos, t_argv, argv_list);
	  log_error("value of content:%s, arg->buffer:%s",content ,arg->buffer);
	  if ((ret = ft_strcmp(content, arg->buffer)) < 0)
	  {
		index++;
		log_error("value of content:%s, arg->buffer:%s, index:%d",content ,arg->buffer, index);
		list_insert(&argument->argv_list, argv_list, index);
		return (ST_OK) ;
	  }
	  else if (ret == 0)
	  {
		index++;
		free(arg->buffer);
		free(arg);
		return (ST_OK) ;
	  }
	  log_error("value of ret: %d",ret);
	  index++;
	}
	if (ret != 0)
		index++;
  }
  log_info("value of content:%s, , index:%d, ret:%d",content , index, ret);
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

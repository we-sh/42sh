#include "shell.h"

/*
** Add a node composed of a string at the end of the list in argument.
*/

int globbing_add_node_to_list(t_list *argv_list, char *content)
{
  t_argv    *argument;
  // t_list    *ptrlist;
  t_argv    *arg;
  t_list  *pos;
  t_list  *safe;

  if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
    return (ST_MALLOC);
  if ((argument->buffer = ft_strdup(content)) == NULL)
    return (ST_MALLOC);
 // ptrlist = argv_list;
  // NEED TO CHECK IF IT ALREADYON THE STRING BEFORE ADDING IT
  safe = argv_list->next;
  while ((pos = safe) && pos != argv_list)
  {
    safe = safe->next;
    arg = CONTAINER_OF(pos, t_argv, argv_list);
    if (ft_strcmp(arg->buffer, content) == 0)
    {
      free(argument->buffer);
      free(argument);
      return(ST_OK);//change return
    }
  }
  list_push_back(&argument->argv_list, argv_list);
  free(argument->buffer);
  free(argument);
  return (ST_OK);
}
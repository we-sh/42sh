#include "shell.h"

/*
** Add a node composed of a string at the end of the list in argument.
*/

int globbing_add_node_to_list(t_list *argv_list, char *content)
{
  t_argv    *argument;
  t_list    *ptrlist;

  if (!(argument = (t_argv *)malloc(sizeof(t_argv))))
    return (ST_MALLOC);
  if ((argument->buffer = ft_strdup(content)) == NULL)
    return (ST_MALLOC);
  ptrlist = argv_list;
  list_push_back(&argument->argv_list, argv_list);
  return (ST_OK);
}
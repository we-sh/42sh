#include "shell.h"

void globbing_happend_to_list(t_mylist **list, char *input)
{
  t_mylist    *newm;
  t_mylist    *ptr;

  // Be careful (*list)->content a cause de globbing_exp_param_bracket
  if (*list == NULL)
  {
    log_info("FIRST: %s", input);
    *list = (t_mylist*)ft_memalloc(sizeof(t_mylist));
    (*list)->content = ft_strdup(input);
    (*list)->next = NULL;
  }
  else
  {
    log_info("Second: %s", input);
    newm = (t_mylist*)ft_memalloc(sizeof(t_mylist));
    ptr = *list;


// FIX LE HAPPEN


    // while (ptr->next)
    // {
    //   log_info("Value of ptr->content `%s'", ptr->content);
    //   if (ft_strcmp(ptr->content, input) == 0)
    //   {
    //     free(newm);
    //     return ;
    //   }
    //   ptr = ptr->next;
    // }
    ptr->next = newm;
    newm->content = ft_strdup(input);
    newm->next = NULL;
  }
}

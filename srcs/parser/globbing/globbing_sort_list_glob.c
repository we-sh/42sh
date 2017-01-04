#include "shell.h"

//REFAIRE LE POP ELEMENT 


// static void   s_pop_elem( t_list **argv_list, t_argv *tmp_arg)
// {
// 	t_list  *pos;
// 	t_list  *safe;
// 	t_argv    *arg;

// 	safe = (*argv_list)->next;
// 	while ((pos = safe) && pos != *argv_list)
// 	{
// 		safe = safe->next;
//     	arg = CONTAINER_OF(pos, t_argv, argv_list);
// 		log_info("2 valeur of arg buff:%s", arg->buffer);
// 		if (ft_strcmp(arg->buffer, tmp_arg->buffer) == 0)
// 		{
// 			t_list_del(safe->prev, safe->next);
// 			free(safe);
// 			free(arg->buffer);
// 			free(arg);
// 			return ;
// 		}
// 	}
// 	exit(0);
// }

void		globbing_sort_list_glob(t_list **argv_list)
{
	t_argv	*argv_cur;
	t_argv	*argv_next;
	t_list	*pos;
	size_t	size;
	size_t	i;

	size = list_size(*argv_list);
	i = 1;
	while (i < size)
	{
		pos = list_nth(*argv_list, i);
		argv_cur = CONTAINER_OF(pos, t_argv, argv_list);
		pos = list_nth(*argv_list, i + 1);
		argv_next = CONTAINER_OF(pos, t_argv, argv_list);
		if (ft_strcmp(argv_cur->buffer, argv_next->buffer) > 0)
		{
			list_move_tail(&argv_next->argv_list, &argv_cur->argv_list);
			i = 0;
		}
		i++;
	}
}

/*
void        globbing_sort_list_glob(t_list **argv_list)
{
	t_list  *newlist;
	t_list  *pos;
	t_list  *safe;
	t_list  *tmp;

	t_argv    *arg;
//	t_argv    *tmp_arg;

	newlist = (t_list *)malloc(sizeof(t_list));
	INIT_LIST_HEAD(newlist);
	safe = (*argv_list)->next;
	while ((pos = safe) && pos != *argv_list)
	{
		tmp = (*argv_list)->next;
		safe = safe->next;
		arg = CONTAINER_OF(pos, t_argv, argv_list);
		log_info("valeur of arg buff:%s", arg->buffer);


	// 	while ((tmp = safe) && tmp != *argv_list)
	// 	{
	// 		log_info("start second loop");
	// 		safe = safe->next;
	// 		tmp_arg = CONTAINER_OF(tmp, t_argv, argv_list);
	// 		if (ft_strcmp(arg->buffer, tmp_arg->buffer) > 0)
	// 			tmp = safe;
	// 		if (list_is_empty(*argv_list) == 1)
	// 		{
	// 			log_info("empty");
	// 			free(*argv_list);
	// 		}
	// 		log_info("end second loop");
	// 	}
		globbing_add_node_to_list(newlist, arg->buffer);
//	 	list_push_front(tmp, newlist);
	// //	s_push_front_in_new_list(&newlist, tmp);
	// 	s_pop_elem(argv_list, tmp_arg);
	// 	safe = (*argv_list)->next;
	}
	log_info("OUT");
	*argv_list = newlist;
}
*/

#include "shell.h"

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

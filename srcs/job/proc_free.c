#include "shell.h"

void	proc_free(t_proc **p)
{
	t_option	*opt;
	t_list		*pos;
	t_list		*safe;
	t_list		*head;

	head = &(*p)->bltin_opt_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		opt = CONTAINER_OF(pos, t_option, list_option);
		option_free(&opt);
	}
	ft_memdel_tab((void ***)&(*p)->argv);
	ft_memdel((void **)&(*p)->command);
	ft_memdel((void **)&(*p));
	*p = NULL;
}

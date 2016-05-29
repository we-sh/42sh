#include "shell.h"

void	job_free(t_job **j)
{
	t_proc	*p;
	t_list	*pos;
	t_list	*safe;
	t_list	*head;

	head = &(*j)->proc_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		p = CONTAINER_OF(pos, t_proc, list_proc);
		proc_free(&p);
		list_del(pos);
	}
	ft_memdel((void **)&(*j)->command);
	ft_memdel((void **)&(*j));
	*j = NULL;
}

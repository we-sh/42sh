#include "shell.h"

void		redir_list_free(t_list *redir_head)
{
	t_list	*head;
	t_list	*safe;
	t_list	*pos;
	t_redir	*redir;

	head = redir_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		redir = CONTAINER_OF(pos, t_redir, list_redir);
		pos->prev->next = safe;
		safe->prev = pos->prev;
		redir_free(&redir);
	}
}

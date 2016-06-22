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
		if (redir->fd > 2)
			close(redir->fd);
		ft_memdel((void **)&redir);
	}
}

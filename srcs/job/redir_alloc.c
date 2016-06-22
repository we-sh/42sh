#include "shell.h"

t_redir		*redir_alloc(int fd)
{
	t_redir	*redir;

	if ((redir = (t_redir *)malloc(sizeof(t_redir))) == NULL)
		return (NULL);
	redir->fd = fd;
	return (redir);
}

#include "shell.h"

void		redir_free(t_redir **redir)
{
	if ((*redir)->fd > 0 && (*redir)->fd != STDIN_FILENO
		&& (*redir)->fd != STDOUT_FILENO && (*redir)->fd != STDERR_FILENO)
		close((*redir)->fd);
	ft_memdel((void **)redir);
}

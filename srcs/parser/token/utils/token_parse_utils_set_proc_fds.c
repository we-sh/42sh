#include "parser.h"

void	token_parse_utils_set_proc_fds(t_proc *p, int fd_l, int fd_r)
{
	if (!(fd_r == STDIN_FILENO
				&& (fd_l == STDOUT_FILENO || fd_l == STDERR_FILENO)))
	{
		if (fd_l == STDIN_FILENO)
		{
			if (p->stdin != STDIN_FILENO)
				close(p->stdin);
			p->stdin = fd_r;
		}
		if (fd_l == STDOUT_FILENO)
		{
			if (p->stdout != STDOUT_FILENO)
				close(p->stdout);
			p->stdout = fd_r;
		}
		if (fd_l == STDERR_FILENO)
		{
			if (p->stderr != STDERR_FILENO)
				close(p->stderr);
			p->stderr = fd_r;
		}
	}
}

#include "parser.h"

int			open_new_fd(t_proc *p, char *f, int *fd, int flag)
{
	if ((*fd = open(f, flag, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
		p->is_valid = 0;
	}
	return (ST_OK);
}

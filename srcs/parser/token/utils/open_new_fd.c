#include "parser.h"

int			open_new_fd(t_proc *p, char *f, int *fd)
{
	if ((*fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
		p->is_valid = 0;
	}
	return (ST_OK);
}

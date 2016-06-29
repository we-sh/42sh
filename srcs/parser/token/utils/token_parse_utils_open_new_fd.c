#include "parser.h"

int			token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag)
{
	if ((*fd = open(f, flag, 0644)) < 0)
	{
		display_status(ST_ENOENT, f, NULL);
		p->is_valid = -1;
	}
	return (ST_OK);
}

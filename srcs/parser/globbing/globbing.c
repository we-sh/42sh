#include "shell.h"

/*
** The purpose of this function is to expand the argument list with the
** globbing function. The argument list is the same pointer before and after
** the call of the globbing function. Only the content is modified.
*/

int	globbing(t_list **argv_list)
{
	int	st;

	log_info("entering globbing");
	if ((st = globbing_interrogation(argv_list)) != ST_OK)
		return (st);
	return (ST_OK);
}

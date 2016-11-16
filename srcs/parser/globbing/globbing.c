#include "shell.h"

int	globbing(t_list **argv_list)
{
	log_info("entering globbing");

	int	st;

	// argv_list is the initial argument list
	if ((st = globbing_interrogation(argv_list)) != ST_OK)
		return (st);
	// argv_list is now the argument list after interrogation globbing
	return (ST_OK);
}

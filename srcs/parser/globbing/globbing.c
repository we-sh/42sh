#include "shell.h"

/*
** Globbing :
** consider `ls "*" *', the loop will receive `\*' and `*'
*/

int	globbing(t_list **argv_list)
{
	log_info("entering globbing");

	int	st;

	if ((st = globbing_brackets(argv_list)) != ST_OK)
		return (st);
	return (ST_OK);
}

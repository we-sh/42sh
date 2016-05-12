#include "shell.h"

/*
** This function is called for the first time and filled in shell_init
*/

int	shell_is_interactive(void)
{
	static int *is_inter;

	if (!is_inter)
	{
		is_inter = (int *)malloc(sizeof(int));
		*is_inter = isatty(STDIN_FILENO);
		log_warn("interactive mode: %s\n", *is_inter ? "TRUE" : "FALSE");
		log_info("ttyname: %s, ttyslot: %d\n", ttyname(STDIN_FILENO), ttyslot());
	}
	return (*is_inter);
}

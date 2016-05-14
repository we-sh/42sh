#include "shell.h"

/*
** This function is called for the first time and filled in shell_init
** It returns negative value when an error occured
*/

int	shell_is_interactive(void)
{
	static int *is_inter = NULL;

	if (is_inter == NULL)
	{
		if ((is_inter = (int *)malloc(sizeof(int))) == NULL)
			return (-ST_MALLOC);
		*is_inter = isatty(STDIN_FILENO);
		log_warn("interactive mode: %s\n", *is_inter ? "TRUE" : "FALSE");
	}
	return (*is_inter);
}

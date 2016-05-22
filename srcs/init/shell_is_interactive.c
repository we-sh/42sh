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
		if (*is_inter)
			log_info("interactive mode enabled");
		else
			log_warn("interactive mode disabled");
	}
	return (*is_inter);
}

#include "shell.h"

/*
** This function exits the Shell and does:
** - display a message error if `status` is different from ST_OK
** - (TODO) set the termios structure to its original value
*/

void	shell_exit(int status)
{
	if (status > ST_OK)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(i18n_translate(status), STDERR_FILENO);
	}
	exit(status);
	//TEMP
	// this will be just a log function
}

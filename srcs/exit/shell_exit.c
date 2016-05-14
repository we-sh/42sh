#include "shell.h"

void	shell_exit(int status)
{
	if (status > ST_OK)
		ft_putendl_fd(i18n_translate(status), STDERR_FILENO);
	exit(status);
}

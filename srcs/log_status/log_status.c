#include "shell.h"

/*
** - display a message error if `status` is different from ST_OK
*/

void	log_status(const int status, const char *info)
{
	if (status > ST_OK)
	{
		ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(i18n_translate(status), STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		if (info)
		{
			ft_putstr_fd(info, STDERR_FILENO);
		}
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

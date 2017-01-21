#include "shell.h"
#include "libftprintf.h"

/*
** - display a message error if `status` is different from ST_OK
*/

int	display_status(const int status, const char *prefix, const char *suffix)
{
	if (status > ST_OK)
	{
		if (prefix && suffix)
			ft_printf("%r%s: %s: %s: %s\n", STDERR_FILENO,
				PROGRAM_NAME, prefix, i18n_translate(status), suffix);
		else if (prefix)
			ft_printf("%r%s: %s: %s\n", STDERR_FILENO,
				PROGRAM_NAME, prefix, i18n_translate(status));
		else if (suffix)
			ft_printf("%r%s: %s: %s\n", STDERR_FILENO,
				PROGRAM_NAME, i18n_translate(status), suffix);
		else
			ft_printf("%r%s: %s\n", STDERR_FILENO,
				PROGRAM_NAME, i18n_translate(status));
	}
	return (status);
}

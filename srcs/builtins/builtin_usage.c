#include "shell.h"

void	builtin_usage(t_builtin const *bltin, int status)
{
	ft_printf("%r%s: %s: %s\n%s: %s\n",
		STDERR_FILENO,
		PROGRAM_NAME,
		bltin->name,
		i18n_translate(status),
		i18n_translate(ST_USAGE),
		bltin->usage);
}

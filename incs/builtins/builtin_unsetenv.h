#ifndef BUILTIN_UNSETENV_H
# define BUILTIN_UNSETENV_H

# include "builtin.h"

static const t_builtin		g_builtin_unsetenv = {
	.index = BLTIN_UNSETENV,
	.name = "unsetenv",
	.usage = "unsetenv [VAR]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_UNSETENV,
	.exe = &builtin_unsetenv,
	.options = NULL
};

#endif

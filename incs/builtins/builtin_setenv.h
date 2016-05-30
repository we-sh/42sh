#ifndef BUILTIN_SETENV_H
# define BUILTIN_SETENV_H

# include "builtin.h"

static const t_builtin		g_builtin_setenv = {
	.index = BLTIN_SETENV,
	.name = "setenv",
	.usage = "setenv [setenv]",
	.description = ST_BLTIN_SETENV,
	.exe = &builtin_setenv,
	.options = NULL
};

#endif

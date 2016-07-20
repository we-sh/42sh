#ifndef BUILTIN_SET_LOCAL_H
# define BUILTIN_SET_LOCAL_H

# include "builtin.h"

static const t_builtin		g_builtin_set_local = {
	.index = BLTIN_SET_LOCAL,
	.name = "setlocal",
	.usage = "setlocal [VAR=[VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_SET_LOCAL,
	.exe = &builtin_set_local,
	.options = NULL
};

#endif

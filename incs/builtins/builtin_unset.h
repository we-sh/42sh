#ifndef BUILTIN_UNSET_H
# define BUILTIN_UNSET_H

# include "builtin.h"

static const t_builtin		g_builtin_unset = {
	.index = BLTIN_UNSET,
	.name = "unset",
	.usage = "unset [NAME...]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_UNSET,
	.exe = &builtin_unset,
	.options = NULL
};
#endif

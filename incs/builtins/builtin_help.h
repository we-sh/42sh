#ifndef BUILTIN_HELP_H
# define BUILTIN_HELP_H

# include "builtin.h"

static const t_builtin		g_builtin_help = {
	.index = BLTIN_HELP,
	.name = "help",
	.usage = "help [builtin]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_HELP,
	.exe = &builtin_help,
	.options = NULL
};

#endif

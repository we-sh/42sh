#ifndef BUILTIN_TERMCAPS_H
# define BUILTIN_TERMCAPS_H

# include "builtin.h"

static const char			*g_builtin_termcaps_usage_multiline[] = {
	[0] = "hello ligne 1",
	[1] = "hello ligne 2",
	[2] = "hello ligne 3",
	[3] = "hello ligne 4",
	[4] = NULL
};

static const t_builtin		g_builtin_termcaps = {
	.index = BLTIN_TERMCAPS,
	.name = "termcaps",
	.usage = "Here we have to describe all the termcaps available",
	.usage_multiline = g_builtin_termcaps_usage_multiline,
	.description = ST_BLTIN_TERMCAPS,
	.exe = &builtin_termcaps,
	.options = NULL
};

#endif

#ifndef BUILTIN_TERMCAPS_H
# define BUILTIN_TERMCAPS_H

# include "builtin.h"

static const t_builtin		g_builtin_termcaps = {
	.index = BLTIN_TERMCAPS,
	.name = "termcaps",
	.usage = "Here we have to describe all the termcaps available",
	.description = ST_BLTIN_TERMCAPS,
	.exe = &builtin_termcaps,
	.options = NULL
};

#endif

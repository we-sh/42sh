#ifndef BUILTIN_FG_H
# define BUILTIN_FG_H

# include "builtin.h"

static const t_builtin		g_builtin_fg = {
	.index = BLTIN_FG,
	.name = "fg",
	.usage = "fg [job_id]",
	.description = ST_BLTIN_FG,
	.exe = &builtin_fg,
	.options = NULL
};

#endif

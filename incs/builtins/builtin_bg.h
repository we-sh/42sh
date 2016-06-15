#ifndef BUILTIN_BG_H
# define BUILTIN_BG_H

# include "builtin.h"


static const t_builtin		g_builtin_bg = {
	.index = BLTIN_BG,
	.name = "bg",
	.usage = "bg [job_id ...]",
	.description = ST_BLTIN_BG,
	.exe = &builtin_bg,
	.options = NULL
};

#endif

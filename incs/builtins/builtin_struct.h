#ifndef BUILTIN_STRUCT_H
# define BUILTIN_STRUCT_H

# include "builtin_cd.h"
# include "builtin_help.h"

/*
** Table of builtins
*/

static const t_builtin		*g_builtins[] = {
	[BLTIN_NONE] = NULL,
	[BLTIN_CD] = &g_builtin_cd,
	[BLTIN_HELP] = &g_builtin_help,
	[BLTIN_TOTAL] = NULL
};

#endif

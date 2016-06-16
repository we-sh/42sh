#ifndef BUILTIN_STRUCT_H
# define BUILTIN_STRUCT_H

# include "builtin_bg.h"
# include "builtin_cd.h"
# include "builtin_exit.h"
# include "builtin_fg.h"
# include "builtin_help.h"
# include "builtin_jobs.h"
# include "builtin_env.h"
# include "builtin_setenv.h"
# include "builtin_unsetenv.h"

/*
** Table of builtins
*/

static const t_builtin		*g_builtins[] = {
	[BLTIN_NONE] = NULL,
	[BLTIN_BG] = &g_builtin_bg,
	[BLTIN_CD] = &g_builtin_cd,
	[BLTIN_EXIT] = &g_builtin_exit,
	[BLTIN_FG] = &g_builtin_fg,
	[BLTIN_HELP] = &g_builtin_help,
	[BLTIN_JOBS] = &g_builtin_jobs,
	[BLTIN_ENV] = &g_builtin_env,
	[BLTIN_SETENV] = &g_builtin_setenv,
	[BLTIN_UNSETENV] = &g_builtin_unsetenv,
	[BLTIN_TOTAL] = NULL
};

#endif

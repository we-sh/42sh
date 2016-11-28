#ifndef BUILTIN_HISTORY_H
# define BUILTIN_HISTORY_H

# include "builtin.h"

static t_option				g_builtin_history_option_i = {
	.name = "i",
	.index = ST_BLTIN_HISTORY_OPT_I,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_history_options[] = {
	[0] = &g_builtin_history_option_i,
	[1] = NULL
};

static const t_builtin		g_builtin_history = {
	.index = BLTIN_HISTORY,
	.name = "history",
	.usage = "history [-i] [VAR=[VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_HISTORY,
	.exe = &builtin_history,
	.options = g_builtin_history_options
};

#endif

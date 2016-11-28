#ifndef BUILTIN_HISTORY_H
# define BUILTIN_HISTORY_H

# include "builtin.h"

static t_option				g_builtin_history_option_c = {
	.name = "c",
	.index = ST_BLTIN_HISTORY_OPT_C,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_d = {
	.name = "d",
	.index = ST_BLTIN_HISTORY_OPT_D,
	.is_single_char = 1,
	.has_value = 1,
	.value_is_numeric = 1,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_w = {
	.name = "w",
	.index = ST_BLTIN_HISTORY_OPT_W,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_r = {
	.name = "r",
	.index = ST_BLTIN_HISTORY_OPT_R,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_a = {
	.name = "a",
	.index = ST_BLTIN_HISTORY_OPT_A,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_n = {
	.name = "n",
	.index = ST_BLTIN_HISTORY_OPT_N,
	.is_single_char = 1,
	.has_value = 0,
	.has_multiple_values = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL,
	.values = NULL
};

static const t_option		*g_builtin_history_options[] = {
	[0] = &g_builtin_history_option_c,
	[1] = &g_builtin_history_option_d,
	[2] = &g_builtin_history_option_w,
	[3] = &g_builtin_history_option_r,
	[4] = &g_builtin_history_option_a,
	[5] = &g_builtin_history_option_n,
	[6] = NULL
};

static const t_builtin		g_builtin_history = {
	.index = BLTIN_HISTORY,
	.name = "history",
	.usage = "history [-c] [-d offset]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_HISTORY,
	.exe = &builtin_history,
	.options = g_builtin_history_options
};

#endif

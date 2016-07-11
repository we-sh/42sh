#ifndef BUILTIN_FOLD_H
# define BUILTIN_FOLD_H

# include "builtin.h"

static t_option				g_builtin_fold_option_s = {
	.name = "s",
	.index = ST_BLTIN_FOLD_OPT_S,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_fold_option_w = {
	.name = "w",
	.index = ST_BLTIN_FOLD_OPT_W,
	.is_single_char = 1,
	.has_value = 1,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_fold_options[] = {
	[0] = &g_builtin_fold_option_s,
	[1] = &g_builtin_fold_option_w,
	[2] = NULL
};

static const t_builtin		g_builtin_fold = {
	.index = BLTIN_FOLD,
	.name = "fold",
	.usage = "fold [-s] [-w width] [file...]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_FOLD,
	.exe = &builtin_fold,
	.options = g_builtin_fold_options
};

#endif

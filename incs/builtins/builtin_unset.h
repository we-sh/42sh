#ifndef BUILTIN_UNSET_H
# define BUILTIN_UNSET_H

# include "builtin.h"

static t_option				g_builtin_unset_option_v = {
	.name = "v",
	.index = ST_BLTIN_UNSET_OPT_V,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_unset_options[] = {
	[0] = &g_builtin_unset_option_v,
	[1] = NULL
};

static const t_builtin		g_builtin_unset = {
	.index = BLTIN_UNSET,
	.name = "unset",
	.usage = "unset [-v] [NAME...]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_UNSET,
	.exe = &builtin_unset,
	.options = g_builtin_unset_options
};
#endif

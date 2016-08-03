#ifndef BUILTIN_EXPORT_H
# define BUILTIN_EXPORT_H

# include "builtin.h"

static t_option				g_builtin_export_option_p = {
	.name = "p",
	.index = ST_BLTIN_EXPORT_OPT_P,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_export_option_n = {
	.name = "n",
	.index = ST_BLTIN_EXPORT_OPT_N,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_export_options[] = {
	[0] = &g_builtin_export_option_p,
	[1] = &g_builtin_export_option_n,
	[2] = NULL
};

static const t_builtin		g_builtin_export = {
	.index = BLTIN_EXPORT,
	.name = "export",
	.usage = "export [-n] [-p] [NAME[=VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_EXPORT,
	.exe = &builtin_export,
	.options = g_builtin_export_options
};

#endif
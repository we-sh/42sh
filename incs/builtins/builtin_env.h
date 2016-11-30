#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include "builtin.h"

static t_option				g_builtin_env_option_i = {
	.name = "i",
	.index = ST_BLTIN_ENV_OPT_I,
	.is_single_char = 1,
	.has_value = 0,
	.has_multiple_values = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL,
	.values = NULL
};

static t_option				g_builtin_env_option_u = {
	.name = "u",
	.index = ST_BLTIN_ENV_OPT_U,
	.is_single_char = 1,
	.has_value = 1,
	.has_multiple_values = 1,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL,
	.values = NULL
};

static const t_option		*g_builtin_env_options[] = {
	[0] = &g_builtin_env_option_i,
	[1] = &g_builtin_env_option_u,
	[2] = NULL
};

static const t_builtin		g_builtin_env = {
	.index = BLTIN_ENV,
	.name = "env",
	.usage = "env [-i] [-u VALUE] [VAR=[VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_ENV,
	.exe = &builtin_env,
	.options = g_builtin_env_options
};

#endif

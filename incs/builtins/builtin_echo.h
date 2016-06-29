#ifndef BUILTIN_ECHO_H
# define BUILTIN_ECHO_H

# include "builtin.h"

char						*builtin_echo_escape(char *str);

static t_option				g_builtin_echo_option_n = {
	.name = "n",
	.index = ST_BLTIN_ECHO_OPT_N,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_echo_option_o = {
	.name = "o",
	.index = ST_BLTIN_ECHO_OPT_O,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_echo_options[] = {
	[0] = &g_builtin_echo_option_n,
	[1] = &g_builtin_echo_option_o,
	[2] = NULL
};

static const t_builtin		g_builtin_echo = {
	.index = BLTIN_ECHO,
	.name = "echo",
	.usage = "echo [-n]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_ECHO,
	.exe = &builtin_echo,
	.options = g_builtin_echo_options
};

#endif

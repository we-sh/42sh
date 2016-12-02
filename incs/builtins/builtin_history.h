#ifndef BUILTIN_HISTORY_H
# define BUILTIN_HISTORY_H

# include "builtin.h"

void	append_history(t_list_head *history, t_proc *p);
void	default_history(t_list_head *history, char *arg);
void	read_history(t_sh *sh, int new);
void	write_history(t_sh *sh, int append);
void	wrap_histfile(t_sh *sh, int opt, char *filename,
						void (*fun)(t_sh *, int));
void	print_history(t_sh *sh, t_proc *p);

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

static t_option				g_builtin_history_option_s = {
	.name = "s",
	.index = ST_BLTIN_HISTORY_OPT_S,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static t_option				g_builtin_history_option_p = {
	.name = "p",
	.index = ST_BLTIN_HISTORY_OPT_P,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_history_options[] = {
	[0] = &g_builtin_history_option_c,
	[1] = &g_builtin_history_option_d,
	[2] = &g_builtin_history_option_w,
	[3] = &g_builtin_history_option_r,
	[4] = &g_builtin_history_option_a,
	[5] = &g_builtin_history_option_n,
	[6] = &g_builtin_history_option_s,
	[7] = &g_builtin_history_option_p,
	[8] = NULL
};

static const t_builtin		g_builtin_history = {
	.index = BLTIN_HISTORY,
	.name = "history",
	.usage = "history: usage: history [-c] [-d offset] [n] or"
	"history -awrn [filename] or history -ps arg [arg...] ",
	.usage_multiline = NULL,
	.description = ST_BLTIN_HISTORY,
	.exe = &builtin_history,
	.options = g_builtin_history_options
};

#endif

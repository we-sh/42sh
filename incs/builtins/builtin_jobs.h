#ifndef BUILTIN_JOBS_H
# define BUILTIN_JOBS_H

# include "builtin.h"

static t_option				g_builtin_jobs_option_l = {
	.name = "l",
	.index = ST_BLTIN_JOBS_OPT_L,
	.is_single_char = 1,
	.has_value = 0,
	.has_multiple_values = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL,
	.values = NULL
};

static t_option				g_builtin_jobs_option_p = {
	.name = "p",
	.index = ST_BLTIN_JOBS_OPT_P,
	.is_single_char = 1,
	.has_value = 0,
	.has_multiple_values = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL,
	.values = NULL
};

static const t_option		*g_builtin_jobs_options[] = {
	[0] = &g_builtin_jobs_option_l,
	[1] = &g_builtin_jobs_option_p,
	[2] = NULL
};

static const t_builtin		g_builtin_jobs = {
	.index = BLTIN_JOBS,
	.name = "jobs",
	.usage = "jobs [-l|-p] [job_id ...]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_JOBS,
	.exe = &builtin_jobs,
	.options = g_builtin_jobs_options
};

#endif

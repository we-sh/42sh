#include "shell.h"

/*
** Generic structure for options.
** This structure may be used as a list or within a static table.
**
** List use case:
** - parse and save options from `char **argv` at runtime
**
** Static table use case:
** - configure available options for the Shell or a builtin at compilation
**
** Convention:
** - an upcase-single-character option (e.g. `-P`) should be suffixed with `2`
** to differentiate with an optional existing other option with the same
** character in downcase (e.g. `-p`)
*/

typedef struct				s_option
{
	t_list					list_option;
	char const				*name;
	char					is_single_char;
	char					has_value;
	char					value_is_numeric_only;
	char					value_is_alnum_only;
	char					*value;
}							t_option;

/*
** -------------------------------------------------------
** Options for builtin `cd`
*/

static t_option				g_builtin_cd_option_p2 = {
	.name = "P",
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric_only = 0,
	.value_is_alnum_only = 0,
	.value = NULL
};

static t_option				g_builtin_cd_option_test = {
	.name = "test",
	.is_single_char = 0,
	.has_value = 1,
	.value_is_numeric_only = 1,
	.value_is_alnum_only = 0,
	.value = NULL
};

static t_option				g_builtin_cd_option_t = {
	.name = "t",
	.is_single_char = 1,
	.has_value = 1,
	.value_is_numeric_only = 1,
	.value_is_alnum_only = 0,
	.value = NULL
};

static const t_option		*g_builtin_cd_options[] = {
	[0] = &g_builtin_cd_option_p2,
	[1] = &g_builtin_cd_option_test,
	[2] = &g_builtin_cd_option_t,
	[3] = NULL
};

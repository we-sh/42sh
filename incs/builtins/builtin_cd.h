#ifndef BUILTIN_CD_H
# define BUILTIN_CD_H

# include "builtin.h"
# include <sys/stat.h>

typedef struct stat			t_stat;

int							builtin_cd_chk_path(char **path, int follow_lnk);
char						*builtin_cd_rm_dotdot(char *path);
int							builtin_cd_readlink(char const *path, char **buf);

static t_option				g_builtin_cd_option_p2 = {
	.name = "P",
	.index = ST_BLTIN_CD_OPT_P2,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_cd_options[] = {
	[0] = &g_builtin_cd_option_p2,
	[1] = NULL
};

static const t_builtin		g_builtin_cd = {
	.index = BLTIN_CD,
	.name = "cd",
	.usage = "cd [-P] [dir]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_CD,
	.exe = &builtin_cd,
	.options = g_builtin_cd_options
};

#endif

#ifndef BUILTIN_LANGUAGE_H
# define BUILTIN_LANGUAGE_H

# include "builtin.h"

static const t_builtin		g_builtin_language = {
	.index = BLTIN_LANGUAGE,
	.name = "language",
	.usage = "language [language]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_LANGUAGE,
	.exe = &builtin_language,
	.options = NULL
};

#endif

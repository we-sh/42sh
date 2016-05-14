#include "shell.h"

char const	*i18n_translate(int status)
{
	return (g_i18n_translations[shell_language(LANG_GET)][status]);
}

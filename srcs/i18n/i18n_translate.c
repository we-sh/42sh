#include "shell.h"
#include "i18n.h"

/*
** This function returns a translation of a status set in the i18n structure.
*/

char const	*i18n_translate(int status)
{
	return (g_i18n_translations[shell_language(LANG_GET)][status]);
}

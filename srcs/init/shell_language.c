#include "shell.h"

/*
** This function can set and get the runtime language.
** Set the argument with the value LANG_GET to request a `get` or use an
** available language from `i18n.h` to change the language.
** This function is first called at initialization to allocate the memory
** and set the default value (LANG_GET + 1) which is the first defined
** language in the enumeration `e_language` (see i18n.h)
*/

int	shell_language(int lang)
{
	static int *current_lang = NULL;

	if (current_lang == NULL)
	{
		if ((current_lang = (int *)malloc(sizeof(int))) == NULL)
			return (-ST_MALLOC);
		*current_lang = LANG_GET + 1;
	}
	if (lang != LANG_GET && lang != *current_lang)
	{
		*current_lang = lang;
	}
	return (*current_lang);
}

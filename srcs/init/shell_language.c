#include "shell.h"

/*
** This function can set or get the runtime language
** Set argument with value LANG_GET to request a get
** This function is first call at initialization to allocate the memory
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
		log_warn("default language: %s (%d)\n",
			i18n_translate(ST_OK),
			*current_lang);
	}
	if (lang != LANG_GET && lang != *current_lang)
	{
		log_warn("changed language from %d to %d\n", *current_lang, lang);
		*current_lang = lang;
	}
	return (*current_lang);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_language.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		log_info("default language: %s (%d)",
			i18n_translate(ST_OK),
			*current_lang);
	}
	if (lang != LANG_GET && lang != *current_lang)
	{
		log_info("changed language from %d to %d", *current_lang, lang);
		*current_lang = lang;
	}
	return (*current_lang);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i18n_translate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function returns a translation of a status set in the i18n structure.
*/

char const	*i18n_translate(int status)
{
	return (g_i18n_translations[shell_language(LANG_GET)][status]);
}

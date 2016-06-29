/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_language.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_SETENV_H
# define BUILTIN_SETENV_H

# include "builtin.h"

static const t_builtin		g_builtin_setenv = {
	.index = BLTIN_SETENV,
	.name = "setenv",
	.usage = "setenv [VAR[word]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_SETENV,
	.exe = &builtin_setenv,
	.options = NULL
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_HELP_H
# define BUILTIN_HELP_H

# include "builtin.h"

static const t_builtin		g_builtin_help = {
	.index = BLTIN_HELP,
	.name = "help",
	.usage = "help [builtin]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_HELP,
	.exe = &builtin_help,
	.options = NULL
};

#endif

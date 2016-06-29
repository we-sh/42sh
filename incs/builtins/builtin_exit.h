/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_EXIT_H
# define BUILTIN_EXIT_H

# include "builtin.h"

static const t_builtin		g_builtin_exit = {
	.index = BLTIN_EXIT,
	.name = "exit",
	.usage = "exit [n]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_EXIT,
	.exe = &builtin_exit,
	.options = NULL
};

#endif

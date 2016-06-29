/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FG_H
# define BUILTIN_FG_H

# include "builtin.h"

static const t_builtin		g_builtin_fg = {
	.index = BLTIN_FG,
	.name = "fg",
	.usage = "fg [job_id]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_FG,
	.exe = &builtin_fg,
	.options = NULL
};

#endif

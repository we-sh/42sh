/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BG_H
# define BUILTIN_BG_H

# include "builtin.h"

static const t_builtin		g_builtin_bg = {
	.index = BLTIN_BG,
	.name = "bg",
	.usage = "bg [job_id ...]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_BG,
	.exe = &builtin_bg,
	.options = NULL
};

#endif

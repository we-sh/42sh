/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_ENV_H
# define BUILTIN_ENV_H

# include "builtin.h"

static t_option				g_builtin_env_option_i = {
	.name = "i",
	.index = ST_BLTIN_ENV_OPT_I,
	.is_single_char = 1,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option		*g_builtin_env_options[] = {
	[0] = &g_builtin_env_option_i,
	[1] = NULL
};

static const t_builtin		g_builtin_env = {
	.index = BLTIN_ENV,
	.name = "env",
	.usage = "env [-i] [VAR=[VALUE]]",
	.usage_multiline = NULL,
	.description = ST_BLTIN_ENV,
	.exe = &builtin_env,
	.options = g_builtin_env_options
};

#endif

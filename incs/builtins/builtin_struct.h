/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_STRUCT_H
# define BUILTIN_STRUCT_H

# include "builtin_bg.h"
# include "builtin_cd.h"
# include "builtin_exit.h"
# include "builtin_fg.h"
# include "builtin_help.h"
# include "builtin_jobs.h"
# include "builtin_env.h"
# include "builtin_language.h"
# include "builtin_setenv.h"
# include "builtin_termcaps.h"
# include "builtin_unsetenv.h"

/*
** Table of builtins
*/

static const t_builtin		*g_builtins[] = {
	[BLTIN_NONE] = NULL,
	[BLTIN_BG] = &g_builtin_bg,
	[BLTIN_CD] = &g_builtin_cd,
	[BLTIN_EXIT] = &g_builtin_exit,
	[BLTIN_FG] = &g_builtin_fg,
	[BLTIN_HELP] = &g_builtin_help,
	[BLTIN_JOBS] = &g_builtin_jobs,
	[BLTIN_ENV] = &g_builtin_env,
	[BLTIN_LANGUAGE] = &g_builtin_language,
	[BLTIN_SETENV] = &g_builtin_setenv,
	[BLTIN_TERMCAPS] = &g_builtin_termcaps,
	[BLTIN_UNSETENV] = &g_builtin_unsetenv,
	[BLTIN_TOTAL] = NULL
};

#endif

#ifndef BUILTIN_H
# define BUILTIN_H

/*
** -------------------------------------------------------
** Builtin structure and associated enum and typedef
*/

typedef enum				e_builtin_index
{
	BLTIN_NONE,
	BLTIN_CD,
	BLTIN_HELP,
	BLTIN_TOTAL
}							t_builtin_index;

typedef enum				e_builtin_callback
{
	BLTIN_CB_BEFORE,
	BLTIN_CB_EXEC,
	BLTIN_CB_AFTER
}							t_builtin_callback;

typedef struct				s_builtin
{
	int						index;
	char const				*name;
	char const				*usage;
	int						description;
	int						(*exe)(struct s_builtin const *, int, t_sh *, t_proc *);
	t_option const 			**options;
}							t_builtin;

/*
** List of builtins prototypes
*/
int							builtin_cd(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_help(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);

/*
** -------------------------------------------------------
** `cd`
*/

static const t_builtin		g_builtin_cd = {
	.index = BLTIN_CD,
	.name = "cd",
	.usage = "cd [-P] [dir]",
	.description = ST_BLTIN_CD,
	.exe = &builtin_cd,
	.options = g_builtin_cd_options
};

static const t_builtin		g_builtin_help = {
	.index = BLTIN_HELP,
	.name = "help",
	.usage = "help [builtin]",
	.description = ST_BLTIN_HELP,
	.exe = &builtin_help,
	.options = NULL
};

/*
** -------------------------------------------------------
** Table of builtins
*/

static const t_builtin		*g_builtins[] = {
	[BLTIN_NONE] = NULL,
	[BLTIN_CD] = &g_builtin_cd,
	[BLTIN_HELP] = &g_builtin_help,
	[BLTIN_TOTAL] = NULL
};

#endif

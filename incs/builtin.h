#ifndef BUILTIN_H
# define BUILTIN_H

/*
** List of builtins prototypes
*/
int							builtin_cd(int callback, t_sh *sh, t_proc *p);

/*
** -------------------------------------------------------
** Builtin structure and associated enum and typedef
*/

typedef enum				e_builtin_index
{
	BLTIN_NONE,
	BLTIN_CD,
	BLTIN_TOTAL
}							t_builtin_index;

typedef enum				e_builtin_callback
{
	BLTIN_CB_BEFORE,
	BLTIN_CB_EXEC,
	BLTIN_CB_AFTER
}							t_builtin_callback;

typedef int 				(*t_builtin_execute)(int, t_sh *, t_proc *);

typedef struct				s_builtin
{
	int						index;
	char const				*name;
	t_builtin_execute		execute;
	t_option const 			**options[];
}							t_builtin;

/*
** -------------------------------------------------------
** `cd`
*/

static const t_builtin		g_builtin_cd = {
	.index = BLTIN_CD,
	.name = "cd",
	.execute = &builtin_cd,
	.options = {
		g_builtin_cd_options
	}
};

/*
** -------------------------------------------------------
** Table of builtins
*/

static const t_builtin		*g_builtins[] = {
	[BLTIN_NONE] = NULL,
	[BLTIN_CD] = &g_builtin_cd
};

#endif

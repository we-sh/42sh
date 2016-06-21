#ifndef BUILTIN_H
# define BUILTIN_H

# include "option.h"


/*
** Builtin structure and associated enum and typedef
*/

typedef enum				e_builtin_index
{
	BLTIN_NONE,
	BLTIN_BG,
	BLTIN_CD,
	BLTIN_EXIT,
	BLTIN_HELP,
	BLTIN_FG,
	BLTIN_JOBS,
	BLTIN_ENV,
	BLTIN_LANGUAGE,
	BLTIN_SETENV,
	BLTIN_TERMCAPS,
	BLTIN_UNSETENV,
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
	char const				**usage_multiline;
	int						description;
	int						(*exe)(struct s_builtin const *, int, t_sh *, t_proc *);
	t_option const 			**options;
}							t_builtin;

/*
** List of builtins prototypes
*/
int							builtin_bg(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_cd(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_exit(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_fg(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_help(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_jobs(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_env(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_language(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_setenv(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_termcaps(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);
int							builtin_unsetenv(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);

#endif

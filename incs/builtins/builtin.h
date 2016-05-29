#ifndef BUILTIN_H
# define BUILTIN_H

# include "option.h"

/*
** Builtin structure and associated enum and typedef
*/

typedef enum				e_builtin_index
{
	BLTIN_NONE,
	BLTIN_CD,
	BLTIN_HELP,
	BLTIN_JOBS,
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
int							builtin_jobs(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p);

#endif
#include "shell.h"

static int	s_before(t_sh *sh, t_proc *p)
{
	(void)p;
	(void)sh;
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	(void)p;
	(void)builtin;
	return (ST_OK);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	(void)p;
	(void)sh;
	return (ST_OK);
}

int			builtin_export(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

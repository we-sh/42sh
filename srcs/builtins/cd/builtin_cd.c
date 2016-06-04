#include "shell.h"

static int	s_before(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		// todo check path and co
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status != ST_OK)
	{
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_proc *p)
{
	if (p->bltin_status == ST_OK)
	{
		if (chdir(p->argv[1]) < 0)
			return (ST_CHDIR);
	}
	return (ST_OK);
}

int			builtin_cd(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(p));
	return (ST_OK);
}

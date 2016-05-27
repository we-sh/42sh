#include "shell.h"

int			s_before(t_sh *sh, t_proc *p)
{
	// do whatever needed before fork (parse arguments, set `builtin_status` to be used within callbacks `exec` and `after`)
	(void)sh;
	(void)p;

	//p->builtin_status = ST_OK; (default value == ST_OK)
	return (ST_OK);
}

int			s_exec(t_sh *sh, t_proc *p)
{
	// do whatever needed within the child process (display)
	// returns an exit status!
	(void)sh;
	(void)p;

	return (EXIT_SUCCESS);
}

int			s_after(t_sh *sh, t_proc *p)
{
	// only called within the last process of a job (last element of the list `list_job`)
	// do whatever needed after job completed (change current directory, exit...)
	(void)sh;

	if (p->builtin_status == ST_OK)
	{
		// options should be pop before
		if (chdir(p->argv[1]) < 0)
			return (ST_CHDIR);
	}
	return (ST_OK);
}

int			builtin_cd(int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

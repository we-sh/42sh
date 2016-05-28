#include "shell.h"

/*
** This is a template for a builtin implementation
**
** `BLTIN_CB_BEFORE`
** A callback called before the process is forked.
** Used to parse arguments, check options and pop their arguments, and set the
** builtin status (p->builtin_status).
** The builtin status may be used to display errors and to give up behaviors
** that may appear during the other callbacks.
**
** `BLTIN_CB_EXEC`
** A callback called within the child process.
** It has no effect on the parent but should be used to display errors and set
** the exit status.
** If this callback does not exit, the function `proc_launch` may execute
** the `execve(2)` with `p->argv` and `p->envp`.
**
** `BLTIN_CB_AFTER`
** A callback called ONLY within the last process of a job, after the job has
** completed.
** It may for example change the environment of the Shell or change the
** current directory.
*/

int			s_before(t_builtin const *builtin, t_sh *sh, t_proc *p)
{
	(void)builtin;
	(void)sh;
	(void)p;
	return (ST_OK);
}

int			s_exec(t_builtin const *builtin, t_sh *sh, t_proc *p)
{
	(void)builtin;
	(void)sh;
	(void)p;
	return (EXIT_SUCCESS);
}

int			s_after(t_builtin const *builtin, t_sh *sh, t_proc *p)
{
	(void)builtin;
	(void)sh;
	(void)p;
	return (ST_OK);
}

int			builtin_template(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(builtin, sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, sh, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(builtin, sh, p));
	return (ST_OK);
}

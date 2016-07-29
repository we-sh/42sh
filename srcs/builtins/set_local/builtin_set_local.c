#include "shell.h"
#include "builtin_set_local.h"

/*
** This is a template for a builtin implementation
** `BLTIN_CB_BEFORE`
** A callback called before the process is forked.
** Used to parse arguments, check options and pop their arguments, and set the
** builtin status (p->bltin_status).
** The builtin status may be used to display errors and to give up behaviors
** that may appear during the other callbacks.
** `BLTIN_CB_EXEC`
** A callback called within the child process.
** It has no effect on the parent but should be used to display errors and set
** the exit status.
** If this callback does not exit, the function `proc_launch` may execute
** the `execve(2)` with `p->argv` and `p->envp`.
** `BLTIN_CB_AFTER`
** A callback called ONLY within the last process of a job, after the job has
** completed.
** It may for example change the environment of the Shell or change the
** current directory.
*/

static int		s_set_local_loop(t_sh **sh, char *local)
{
	int			flag;
	int			ret;
	t_var		*ptrvar;

	ptrvar = (*sh)->local_vars;
	ret = 0;
	flag = 0;
	while (ptrvar)
	{
		if ((ret = builtin_local_var_update(ptrvar, local, &flag))
			== ST_OK)
			break ;
		else if (ret == ST_MALLOC)
			return (ret);
		ptrvar = ptrvar->next;
	}
	if (flag == 0)
	{
		if ((builtin_local_var_add(sh, local)) == ST_MALLOC)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int		s_exec(t_sh *sh, t_proc *p)
{
	t_var		*ptrvar;

	if (p->bltin_status == ST_OK && p->argc == 1)
	{
		ft_putendl_fd("Local variables", STDOUT_FILENO);
		ptrvar = sh->local_vars;
		while (ptrvar)
		{
			ft_putstr_fd(ptrvar->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(ptrvar->value, STDOUT_FILENO);
			ptrvar = ptrvar->next;
		}
	}
	return (ST_OK);
}

static int		s_after(t_sh **sh, t_proc *p)
{
	int			i;

	i = 1;
	while (p->argv[i])
	{
		if ((s_set_local_loop(sh, p->argv[i])) == ST_MALLOC)
			return (ST_MALLOC);
		i++;
	}
	return (ST_OK);
}

int			builtin_set_local(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	(void)builtin;
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}

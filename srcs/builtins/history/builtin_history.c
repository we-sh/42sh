#include "shell.h"
#include "builtin_history.h"

/*
** This is a template for a builtin implementation
** `BLTIN_CB_after`
** A callback called after the process is forked.
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

static void	s_clear_history(t_sh *sh)
{
	history_clear(&sh->termcaps_context.history);
	sh->termcaps_context.history_initial_size = 0;
}

static void	s_delete_entry(t_sh *sh, t_proc *p)
{
	char			*arg;
	size_t			offset;

	arg = option_get_value(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_D);
	offset = ft_atoi(arg);
	history_remove(&sh->termcaps_context.history, offset + 1);
}

static int	s_after(t_builtin const *builtin, t_sh *sh, t_proc *p)
{
	(void)builtin;
	log_debug("builtin status: %d argc %d\n", p->bltin_status, p->argc);
	if (p->bltin_status != ST_OK)
		return (EXIT_SUCCESS);
	if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_C) == 1)
		s_clear_history(sh);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_D) == 1)
		s_delete_entry(sh, p);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_W) == 1)
		write_history(sh, 0, p->argv[1]);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_R) == 1)
		read_history(sh, 0, p->argv[1]);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_A) == 1)
		write_history(sh, 1, p->argv[1]);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_N) == 1)
		read_history(sh, 1, p->argv[1]);
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_S) == 1)
		append_history(&sh->termcaps_context.history, p);
	else
		default_history(&sh->termcaps_context.history, p->argv[1]);
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status == ST_OK)
		return (EXIT_SUCCESS);
	else
	{
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			builtin_history(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(builtin, sh, p));
	return (ST_OK);
}

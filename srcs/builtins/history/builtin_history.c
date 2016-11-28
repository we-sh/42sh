#include "shell.h"

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

static int	s_before(t_builtin const *builtin, t_sh *sh, t_proc *p)
{
	t_node_history	*node;
	t_list			*pos;
	char			*arg;
	size_t			offset;

	(void)builtin;
	log_debug("builtin status: %d argc %d\n", p->bltin_status, p->argc);
	if (p->bltin_status != ST_OK)
		return (EXIT_SUCCESS);
	if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_C) == 1)
	{
		log_debug("history Option -c");
		history_clear(&sh->termcaps_context.history);
		sh->termcaps_context.history_initial_size = 0;
	}
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_D) == 1)
	{
		log_debug("history Option -d");
		arg = option_get_value(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_D);
		offset = ft_atoi(arg);
		history_remove(&sh->termcaps_context.history, offset + 1);
	}
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_W) == 1)
	{
		log_debug("history Option -w");
		history_write(&sh->termcaps_context.history, sh->termcaps_context.history_file, 0);
	}
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_R) == 1)
	{
		log_debug("history Option -r");
		offset = 0;
		history_load(sh->termcaps_context.history_file, &sh->termcaps_context.history, &offset);
		if (offset > sh->termcaps_context.history_initial_size)
			sh->termcaps_context.history_initial_size = offset;
	}
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_A) == 1)
	{
		log_debug("history Option -a");
		history_write(&sh->termcaps_context.history, sh->termcaps_context.history_file, 1);
		sh->termcaps_context.history_initial_size = sh->termcaps_context.history.size;
	}
	else if (option_is_set(&p->bltin_opt_head, ST_BLTIN_HISTORY_OPT_N) == 1)
	{
		log_debug("history Option -n");
		history_load(sh->termcaps_context.history_file, &sh->termcaps_context.history, &sh->termcaps_context.history_initial_size);
		sh->termcaps_context.history_initial_size = sh->termcaps_context.history.size;
	}
	else
	{
		log_debug("history No Option");
		offset = 0;
		pos = &sh->termcaps_context.history.list;
		while ((pos = pos->next) && pos != &sh->termcaps_context.history.list)
		{
			node = CONTAINER_OF(pos, t_node_history, list);
			ft_printf("%s %4d %.*s\n", node->is_modified ? "*" : " ", offset, (int)node->command.size, node->command.bytes);
			offset++;
		}
	}
	return (ST_OK);
}

static int		s_exec(t_sh *sh, t_proc *p)
{
	(void)sh;
	(void)p;
	return (EXIT_SUCCESS);
}

static int		s_after(t_sh **sh, t_proc *p)
{
	(void)sh;
	(void)p;
	return (ST_OK);
}

int				builtin_history(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(builtin, sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}

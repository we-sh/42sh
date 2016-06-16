#include "shell.h"

static int	s_before_with_arg(t_proc *p)
{
	t_job	*j;

	if ((j = job_by_name(p->argv[1], 0)) == NULL)
	{
		p->bltin_status = ST_BLTIN_BG_ERR_JOBNOTFOUND;
		if ((p->bltin_char = ft_strdup(p->argv[1])) == NULL)
			return (ST_MALLOC);
	}
	return (ST_OK);
}

static int	s_before(t_proc *p)
{
	t_job	*j;

	if (p->bltin_status != ST_OK)
		return (ST_OK);
	if (p->argc > 2)
	{
		p->bltin_status = ST_EINVAL;
		return (ST_OK);
	}
	if (p->argc == 2)
		return (s_before_with_arg(p));
	if ((j = job_by_name("%%", 0)) == NULL)
		p->bltin_status = ST_BLTIN_BG_ERR_JOBNOTFOUND;
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status > ST_OK)
	{
		if (p->bltin_status == ST_EINVAL)
			builtin_usage(builtin, p->bltin_status);
		else
			display_status(p->bltin_status, "fg", p->bltin_char);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	t_job	*j;

	if (p->bltin_status == ST_OK)
	{
		j = NULL;
		if (p->argc == 2)
			j = job_by_name(p->argv[1], 0);
		else
			j = job_by_name("%%", 0);
		if (j)
			job_foreground(sh, j, 1);
	}
	return (ST_OK);
}

int			builtin_fg(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

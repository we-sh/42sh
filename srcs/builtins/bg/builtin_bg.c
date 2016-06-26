#include "shell.h"

static int	s_before_with_args(t_proc *p)
{
	int		i;
	t_job	*j;

	i = 1;
	while (i < p->argc)
	{
		if ((j = job_by_name(p->argv[i], 0)) == NULL)
			p->bltin_status = ST_BLTIN_BG_ERR_JOBNOTFOUND;
		else if (job_is_stopped(j) == 0)
			p->bltin_status = ST_BLTIN_BG_ERR_ALREADYBG;
		if (p->bltin_status != ST_OK)
		{
			if ((p->bltin_char = ft_strdup(p->argv[i])) == NULL)
				return (ST_MALLOC);
			break ;
		}
		i++;
	}
	return (ST_OK);
}

static int	s_before(t_proc *p)
{
	t_job	*j;

	if (p->bltin_status != ST_OK)
		return (ST_OK);
	if (p->argc > 1)
		return (s_before_with_args(p));
	if ((j = job_by_name("%%", 0)) == NULL)
		p->bltin_status = ST_BLTIN_BG_ERR_JOBNOTFOUND;
	else if (job_is_stopped(j) == 0)
		p->bltin_status = ST_BLTIN_BG_ERR_ALREADYBG;
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status > ST_OK)
	{
		if (p->bltin_status == ST_EINVAL)
			builtin_usage(builtin, p->bltin_status);
		else
			display_status(p->bltin_status, "bg", p->bltin_char);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	int		i;
	t_job	*j;

	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 1)
		{
			i = 1;
			while (i < p->argc)
			{
				if ((j = job_by_name(p->argv[i], 0)) != NULL)
					return (job_background(sh, j, 1));
				i++;
			}
		}
		else if ((j = job_by_name("%%", 0)) != NULL)
			return (job_background(sh, j, 1));
	}
	return (ST_OK);
}

int			builtin_bg(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

#include "shell.h"

int			s_before(t_builtin const *builtin, t_proc *p)
{
	int		ret;

	log_debug("builtin callback cd: before");
	if ((ret = option_parse(&p->builtin_options_head, builtin->options, &p->argv, 1)) != ST_OK)
	{
		if (ret != ST_EINVAL)
		{
			log_fatal("parsing builtin option failed");
			return (ret);
		}
		p->builtin_status = ret;
	}
	return (ST_OK);
}

int			s_exec(t_proc *p)
{
	log_debug("builtin callback cd: exec");
	if (p->builtin_status != ST_OK)
	{
		// todo use `log_status()` instead
		ft_putendl_fd(i18n_translate(p->builtin_status), STDERR_FILENO);
	}
	return (EXIT_SUCCESS);
}

int			s_after(t_proc *p)
{
	log_debug("builtin callback cd: after");
	if (p->builtin_status == ST_OK)
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
		return (s_before(builtin, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(p));
	return (ST_OK);
}

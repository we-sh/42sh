#include "shell.h"
#include "i18n.h"

static int	s_before(t_proc *p)
{
	int		i;

	if (p->argc != 2)
	{
		if (p->argc == 1)
			p->bltin_status = ST_EINVAL;
		else
			p->bltin_status = ST_E2BIG;
	}
	else
	{
		i = 1;
		while (g_language_identifiers[i])
		{
			if (ft_strcmp(p->argv[1], g_language_identifiers[i]) == 0)
			{
				p->bltin_status = -i;
				return (ST_OK);
			}
			i++;
		}
		p->bltin_status = ST_BLTIN_LANGUAGE_ERR_NOTFOUND;
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status > ST_OK)
	{
		if (p->bltin_status == ST_BLTIN_LANGUAGE_ERR_NOTFOUND)
			display_status(p->bltin_status, "language", p->argv[1]);
		else
			builtin_usage(builtin, p->bltin_status);
	}
	else
	{
		shell_language(-p->bltin_status);
		ft_printf("%s: %s\n", i18n_translate(ST_BLTIN_LANGUAGE_OK),
			i18n_translate(ST_OK));
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_proc *p)
{
	if (p->bltin_status < ST_OK)
	{
		shell_language(-p->bltin_status);
	}
	return (ST_OK);
}

int			builtin_language(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
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

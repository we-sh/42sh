#include "shell.h"
#include "builtin_struct.h"

static int	s_before(t_proc *p)
{
	int	i;
	int	exists;

	if (p->argc > 2)
		p->bltin_status = ST_E2BIG;
	else
	{
		exists = 0;
		i = BLTIN_NONE;
		while (++i < BLTIN_TOTAL)
		{
			if (ft_strcmp(p->argv[1], g_builtins[i]->name) == 0)
			{
				p->bltin_status = -i;
				exists = 1;
				break;
			}
		}
		if (exists == 0)
			p->bltin_status = ST_EINVAL;
	}
	return (ST_OK);
}

static int	s_display_help(t_builtin const *bltin)
{
	int	i;

	ft_printf("%s\n%s: %s\n",
		i18n_translate(bltin->description),
		i18n_translate(ST_USAGE),
		bltin->usage);
	i = BLTIN_NONE;
	while (++i < BLTIN_TOTAL)
	{
		ft_printf(" %-10s: %s\n",
			g_builtins[i]->name,
			i18n_translate(g_builtins[i]->description));
	}
	return (EXIT_SUCCESS);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	int i;

	if (p->bltin_status > ST_OK)
	{
		builtin_usage(builtin, p->bltin_status);
		return (EXIT_FAILURE);
	}
	if (p->argc == 1)
		return (s_display_help(builtin));
	ft_putstr(g_builtins[-p->bltin_status]->name);
	ft_putstr(": ");
	ft_putendl(g_builtins[-p->bltin_status]->usage);
	ft_putendl(i18n_translate(g_builtins[-p->bltin_status]->description));
	if (g_builtins[-p->bltin_status]->options != NULL)
	{
		ft_putendl("options:");
		i = 0;
		while (g_builtins[-p->bltin_status]->options[i])
		{
			ft_putstr(" `");
			ft_putstr(g_builtins[-p->bltin_status]->options[i]->name);
			ft_putstr("` ");
			ft_putendl(i18n_translate(g_builtins[-p->bltin_status]->options[i]->index));
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int			builtin_help(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	(void)sh;
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	return (ST_OK);
}

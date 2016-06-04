#include "shell.h"
#include "builtin_struct.h"

static int		s_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	builtin_callback(int callback, t_sh *sh, t_proc *p)
{
	int	i;

	i = BLTIN_NONE;
	while (++i < BLTIN_TOTAL)
	{
		if (ft_strcmp(p->argv[0], g_builtins[i]->name) == 0)
		{
			if (callback == BLTIN_CB_BEFORE && g_builtins[i]->options != NULL)
			{
				p->bltin_status = option_parse(&p->bltin_opt_head,
					g_builtins[i]->options, &p->argv, 1);
				p->argc = s_argc(p->argv);
				if (p->bltin_status != ST_OK
					&& p->bltin_status != ST_EINVAL)
				{
					log_fatal("parsing builtin options failed");
					return (p->bltin_status);
				}
			}
			return (g_builtins[i]->exe(g_builtins[i], callback, sh, p));
		}
	}
	return (ST_OK);
}

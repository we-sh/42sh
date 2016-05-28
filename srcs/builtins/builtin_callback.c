#include "shell.h"
#include "builtin_struct.h"

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
				p->builtin_status = option_parse(&p->builtin_options_head,
					g_builtins[i]->options, &p->argv, 1);
				if (p->builtin_status != ST_OK
					&& p->builtin_status != ST_EINVAL)
				{
					log_fatal("parsing builtin options failed");
					return (p->builtin_status);
				}
			}
			return (g_builtins[i]->exe(g_builtins[i], callback, sh, p));
		}
	}
	return (ST_OK);
}

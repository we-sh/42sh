#include "shell.h"

int	builtin_callback(int callback, t_sh *sh, t_proc *p)
{
	int	i;

	i = BLTIN_NONE;
	while (++i < BLTIN_TOTAL)
	{
		if (ft_strcmp(p->argv[0], g_builtins[i]->name) == 0)
		{
			return (g_builtins[i]->exe(g_builtins[i], callback, sh, p));
		}
	}
	return (ST_OK);
}

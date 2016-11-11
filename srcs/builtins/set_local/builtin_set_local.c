#include "shell.h"
#include "builtin_set_local.h"

static int		s_exec(t_sh *sh, t_proc *p)
{
	t_var	*ptrvar;

	if (p->bltin_status == ST_OK && p->argc == 1)
	{
		ft_putendl_fd("Local value :", STDOUT_FILENO);
		ptrvar = sh->local_vars;
		while (ptrvar != NULL)
		{
			ft_putstr_fd(ptrvar->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			if (ptrvar->value)
				ft_putendl_fd(ptrvar->value, STDOUT_FILENO);
			else
				ft_putendl_fd("\0", STDOUT_FILENO);
			ptrvar = ptrvar->next;
		}
	}
	return (ST_OK);
}

static int	s_after(t_sh **sh, t_proc *p)
{
	int			i;
	char		*tmp;
	char		*value;

	i = 1;
	while (p->argv[i])
	{
		if ((tmp = ft_strdup(p->argv[i])) == NULL)
			return (ST_MALLOC);
		value = env_get_value_and_remove_equal_sign(tmp);
		if ((builtin_local_var_set_local_loop(sh, tmp, value)) == ST_MALLOC)
			return (ST_MALLOC);
		free(tmp);
		i++;
	}
	return (ST_OK);
}

int				builtin_set_local(t_builtin const *builtin,
							int callback, t_sh *sh, t_proc *p)
{
	(void)builtin;
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(&sh, p));
	return (ST_OK);
}

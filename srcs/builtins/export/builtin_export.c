#include "shell.h"

static int	s_exec_display(t_proc *p, t_sh *sh)
{
	t_var	*ptr;
	int		i;

	i = 0;
	ptr = sh->local_vars;
	if (p->argc == 1)
		p->argc--;
	if (p->argc == 0)
	{
		while (p->envp[i])
		{
			ft_putendl_fd(p->envp[i], STDOUT_FILENO);
			i++;
		}
		while (ptr)
		{
			ft_putstr_fd(ptr->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putendl_fd(ptr->value, STDOUT_FILENO);
			ptr =ptr->next;
		}
		exit(EXIT_SUCCESS);
	}
	return (ST_OK);
}


static int	s_before(t_sh *sh, t_proc *p)
{
	(void)p;
	(void)sh;
	return (ST_OK);
}

static int	s_exec(t_sh *sh, t_builtin const *builtin, t_proc *p)
{
	int ret;

	ret = 0;
	if (p->bltin_status == ST_OK || p->argc == 0)
	{
		if ((ret = option_is_set(&p->bltin_opt_head, ST_BLTIN_EXPORT_OPT_P)) == 1)
			s_exec_display(p, sh);
		else
			s_exec_display(p, sh);
	}
	else
	{
		builtin_usage(builtin, p->bltin_status);
		exit(EXIT_FAILURE);
	}
	return (ST_OK);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	(void)p;
	(void)sh;
	return (ST_OK);
}

int			builtin_export(t_builtin const *builtin,
						int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(sh, builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

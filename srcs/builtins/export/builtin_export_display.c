#include "shell.h"
#include "builtin_set_local.h"

static void		s_display_local(t_proc *p, t_var *ptrvar)
{
	int			i;
	int			key_len;

	i = 0;
	key_len = ft_strlen(ptrvar->key);
	while (p->envp[i])
	{
		if (strncmp(ptrvar->key, p->envp[i], key_len) == 0)
		{
			ptrvar = ptrvar->next;
			return ;
		}
		i++;
	}
	ft_putstr_fd(ptrvar->key, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	if (ptrvar->value)
		ft_putendl_fd(ptrvar->value, STDOUT_FILENO);
	else
		ft_putendl_fd("\0", STDOUT_FILENO);
	return ;
}

void			builtin_export_display(t_sh *sh, t_proc *p)
{
	int			i;
	t_var		*ptrvar;

	ptrvar = sh->local_vars;
	i = 0;
	if (p->argc == 1)
		p->argc--;
	if (p->argc == 0)
	{
		while (p->envp[i])
		{
			ft_putendl_fd(p->envp[i], STDOUT_FILENO);
			i++;
		}
		i = 0;
		while (ptrvar)
		{
			s_display_local(p, ptrvar);
			ptrvar = ptrvar->next;
		}
	}
}

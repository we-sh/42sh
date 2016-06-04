#include "shell.h"

static char	**s_unsetenv_unset(t_sh *sh, int pos)
{
	char		**tmp;
	int			i;
	int			j;
	int			size;
//CHECK DES RETURN ST_MALLOC
	i = 0;
	j = 0;
	size = 0;
	tmp = NULL;
	log_info("position : %d ", pos);
	while (sh->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(char *) * size);
	log_info("size : %d ", size+1);
	while (sh->envp[i]) //improve this
	{
		log_info("sh->envp[%d] : %s", i, sh->envp[i]);
		if (i != pos)
			tmp[j++] = ft_strdup(sh->envp[i++]);
		else
			i++;
	}
	tmp[j] = NULL;
	log_info("sh->envp[%d] : %s", i, sh->envp[i]);
	ft_memdel_tab((void ***)&sh->envp);
	return (tmp);
}

static int	s_env_check_if_unset(t_sh *sh, t_proc *p)
{
	int		ret;

	if ((ret = env_index_value(sh, p->argv[1])) == -1)
		return (ST_OK); //I don't care Bro
	else
		sh->envp = s_unsetenv_unset(sh, ret);
	return (ST_OK);
}

static int	s_before(t_proc *p)
{
	int		ret;

	ret = 0;
	if (p->bltin_status == ST_OK)
	{
		if (p->argc == 1)
			p->bltin_status = ST_E2SMALL;
		else
			p->bltin_status = ST_OK;
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status != ST_OK)
	{
		ft_putendl_fd(i18n_translate(p->bltin_status), STDERR_FILENO);
		if (p->bltin_status == ST_EINVAL)
		{
			ft_putstr_fd(i18n_translate(ST_USAGE), STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(builtin->usage, STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	int		i;

	i = 1;
	if (p->bltin_status == ST_OK)
	{
		while (p->argv[i])
		{
			s_env_check_if_unset(sh, p);
			i++;
		}
	}
	p->bltin_status = ST_OK;
	return (ST_OK);
}

int			builtin_unsetenv(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

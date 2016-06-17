#include "shell.h"
#include "builtin_cd.h"

static int	s_set_bltin_char(t_sh *sh, t_proc *p)
{
	char	*str;

	if (p->argc == 1)
	{
		if ((str = env_get(p->envp, "HOME")) == NULL)
			p->bltin_status = ST_BLTIN_CD_ERR_MISSINGHOME;
		p->bltin_char = ft_strdup(str);
	}
	else if (ft_strcmp(p->argv[1], "-") == 0)
	{
		if ((str = env_get(p->envp, "OLDPWD")) == NULL)
			p->bltin_status = ST_BLTIN_CD_ERR_MISSINGOLDPWD;
		p->bltin_char = ft_strdup(str);
	}
	else
	{
		if (p->argc == 2 && p->argv[1][0] == '/')
			p->bltin_char = ft_strdup(p->argv[1]);
		else if (p->argc == 2)
			p->bltin_char = ft_strjoin3(sh->pwd, "/", p->argv[1]);
	}
	if (p->bltin_char == NULL)
		return (ST_MALLOC);
	return (ST_OK);
}

static int	s_before(t_sh *sh, t_proc *p)
{
	int		ret;

	if (p->bltin_status == ST_OK)
	{
		if (p->argc > 2)
			p->bltin_status = ST_E2BIG;
		else
		{
			if ((ret = s_set_bltin_char(sh, p)) != ST_OK)
				return (ret);
			if ((p->bltin_char = builtin_cd_rm_dotdot(p->bltin_char)) == NULL)
				return (ST_MALLOC);
			p->bltin_status = builtin_cd_chk_path(&p->bltin_char,
				option_is_set(&p->bltin_opt_head, ST_BLTIN_CD_OPT_P2));
		}
	}
	return (ST_OK);
}

static int	s_exec(t_builtin const *builtin, t_proc *p)
{
	if (p->bltin_status != ST_OK)
	{
		if (p->bltin_status == ST_EINVAL)
			builtin_usage(builtin, p->bltin_status);
		else
		{
			if (p->argc == 2 && ft_strcmp(p->argv[1], "-") != 0)
				display_status(p->bltin_status, NULL, p->argv[1]);
			else if (p->argc == 1)
				display_status(p->bltin_status, NULL, env_get(p->envp, "HOME"));
			else
				display_status(p->bltin_status, NULL, NULL);
		}
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	s_after(t_sh *sh, t_proc *p)
{
	int			ret;

	if (p->bltin_status == ST_OK)
	{
		if (chdir(p->bltin_char) < 0)
			return (ST_CHDIR);
		if ((ret = env_set(&sh->envp, "OLDPWD", sh->pwd)) != ST_OK)
			return (ret);
		if ((ret = env_set(&sh->envp, "PWD", p->bltin_char)) != ST_OK)
			return (ret);
		ft_memdel((void **)&sh->pwd);
		if ((sh->pwd = ft_strdup(p->bltin_char)) == NULL)
			return(ST_MALLOC);
	}
	return (ST_OK);
}

int			builtin_cd(t_builtin const *builtin, int callback, t_sh *sh, t_proc *p)
{
	if (callback == BLTIN_CB_BEFORE)
		return (s_before(sh, p));
	if (callback == BLTIN_CB_EXEC)
		exit(s_exec(builtin, p));
	if (callback == BLTIN_CB_AFTER)
		return (s_after(sh, p));
	return (ST_OK);
}

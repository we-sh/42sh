#include "shell.h"

/*
** -> if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL)
** man 3 a verifier si seul moyen de le recuperer
*/

static int s_env_set_default_pwd(char **defaultenv)
{
	char	*tmp;

	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (ST_MALLOC);
	if ((*defaultenv = ft_strjoin("PWD=", tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}

static char	**s_environment_default(void)
{
	char	**defaultenv;

	if ((defaultenv = (char **)malloc(sizeof(char *) * 9)) == NULL)
		return (NULL);
	if ((defaultenv[0] = ft_strjoin("TERM=", env_get_term(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[1] = ft_strjoin("PATH=", env_get_path(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[2] = ft_strjoin("USER=", env_get_user(NULL))) == NULL)
		return (NULL);
	if ((defaultenv[3] = ft_strdup("SHLVL=1")) == NULL)
		return (NULL);
	if ((defaultenv[4] = ft_strjoin("HOME=", env_get_home(NULL))) == NULL)
		return (NULL);
	if (s_env_set_default_pwd(&defaultenv[5]) != ST_OK)
		return (NULL);
	if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL)
		return (NULL);
	if ((defaultenv[7] = ft_strdup("SHELL=wesh")) == NULL)
		return (NULL);
	defaultenv[8] = NULL;
	return (defaultenv);
}

static int	s_default_vars(char ***envp)
{
	if (env_get(*envp, "PATH") == NULL)
		env_set(envp, "PATH", env_get_path(*envp));
	return (ST_OK);
}

int			shell_environment(t_sh *sh, char **envp)
{
	int		i;

	i = 0;
	if (envp[i] == NULL)
	{
		if ((sh->envp = s_environment_default()) == NULL)
			return (ST_MALLOC);
		return (ST_OK);
	}
	while (envp[i])
		i++;
	if ((sh->envp = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (ST_MALLOC);
	i = 0;
	while (envp[i])
	{
		if ((sh->envp[i] = ft_strdup(envp[i])) == NULL)
			return (ST_MALLOC);
		i++;
	}
	sh->envp[i] = NULL;
	return (s_default_vars(&sh->envp));
}

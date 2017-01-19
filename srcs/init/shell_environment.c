#include "shell.h"

/*
** -> if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL)
** man 3 a verifier si seul moyen de le recuperer
*/

static int	s_env_set_default_pwd(char **defaultenv)
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
	if ((defaultenv[7] = ft_strdup("SHELL=bash")) == NULL)
		return (NULL);
	defaultenv[8] = NULL;
	return (defaultenv);
}

static int	s_env_set_new_shlvl(char **shenv, char *env_shlvl)
{
	int		value;
	char	*strvalue;

	value = 0;
	while (*env_shlvl != '\0')
	{
		if (*env_shlvl == '=')
		{
			value = ft_atoi(++env_shlvl) + 1;
			break ;
		}
		env_shlvl += 1;
	}
	if ((strvalue = ft_itoa(value)) == NULL)
		return (ST_MALLOC);
	if ((*shenv = ft_strjoin("SHLVL=", strvalue)) == NULL)
		return (ST_MALLOC);
	free(strvalue);
	return (ST_OK);
}

static int	s_env_fill_shenv(t_sh *sh, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			if (((s_env_set_new_shlvl(&sh->envp[i], envp[i]))) == ST_MALLOC)
				return (ST_MALLOC);
		}
		else if (ft_strncmp(envp[i], "SHELL", 5) == 0)
		{
			if ((sh->envp[i] = ft_strdup("SHELL=bash")) == NULL)
				return (ST_MALLOC);
		}
		else if ((sh->envp[i] = ft_strdup(envp[i])) == NULL)
			return (ST_MALLOC);
		i++;
	}
	sh->envp[i] = NULL;
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
	s_env_fill_shenv(sh, envp);
	if (env_get(sh->envp, "PATH") == NULL)
		env_set(&sh->envp, "PATH", env_get_path(sh->envp));
	return (ST_OK);
}

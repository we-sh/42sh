#include "shell.h"


static char	**s_environment_default(void)
{
	char	**defaultenv;
	char	*tmp;

	if ((defaultenv = (char **)malloc(sizeof(char *) * 8)) == NULL)
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
	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NULL);
	if ((defaultenv[5] = ft_strjoin("PWD=", tmp)) == NULL)
		return (NULL);
	free(tmp);
	if ((defaultenv[6] = ft_strjoin("LOGNAME=", getlogin())) == NULL) // man 3 a verifier seul moyen de le recuperer
		return (NULL);
	defaultenv[7] = NULL;
	return (defaultenv);
}


int			shell_environment(t_sh *sh, char **envp)
{
	int		i;

	i = 0;
	if (envp[i] == NULL)
	{
		if ((sh->envp = s_environment_default()) == NULL)
			return (ST_MALLOC);
		return (ST_OK); // Set Default return
	}
	while (envp[i])
		i++;
	if ((sh->envp = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (ST_MALLOC);
	i = 0;
	while (envp[i])
	{
		 if ((sh->envp[i] = strdup(envp[i])) == NULL)
		 	return (ST_MALLOC);
		 i++;
	}
	sh->envp[i] = NULL;
	return (ST_OK);
}

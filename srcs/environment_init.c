#include "shell.h"


static	char	**s_environment_default(void)
{
	char	**defaultenv;
	char	tmp[PATH_MAX];

	defaultenv = (char **)malloc(sizeof(char *) * 8);
	defaultenv[0] = ft_strjoin("TERM=", env_get_term(NULL));
	defaultenv[1] = ft_strjoin("PATH=", env_get_path(NULL));
	defaultenv[2] = ft_strjoin("USER=", env_get_user(NULL));
	defaultenv[3] = ft_strdup("SHLVL=1");
	defaultenv[4] = ft_strjoin("HOME=", env_get_home(NULL));
	defaultenv[5] = ft_strjoin("PWD=", getcwd(tmp, PATH_MAX));
	defaultenv[6] = ft_strjoin("LOGNAME=", getlogin()); // man 3 a verifier seul moyen de le recuperer
	defaultenv[7] = NULL;
	return (defaultenv);
}


int		environment_init(t_sh *sh, char **envp)
{
	int i;

	i = 0;
	if (envp[i] == NULL)
	{
		sh->envp = s_environment_default();
		return (ST_OK); // Set Default return
	}
	while (envp[i])
		i++;
	sh->envp = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		 if ((sh->envp[i] = strdup(envp[i])) == NULL)
		 {
		 	log_fatal("ft_strdup failded because of insuffisant memory availale");
		 	return (-ST_MALLOC);
		 }
		 i++;
	}
	sh->envp[i] = NULL;
	return (ST_OK);
}

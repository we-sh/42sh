#include "shell.h"
	

static	int		s_environment_default(char **env)
{
	env = (char **)malloc(sizeof(char *) * 2); // A definir
	env[0] = ft_strdup("DEFAULT=DEFAULT");
	env[1] = NULL;
	return (0);
}


int		environment_init(t_sh *sh, const char *envp[])
{
	int i;
	int j;

	i = 0;
	if (envp[i] == NULL)
	{
		s_environment_default(sh->envp);
		return (1); // Set Default return
	}
	while (envp[i])
		i++;
	j = 0;
	sh->envp = (char **)malloc(sizeof(char *) * i);
	while (envp[j])
	{			
		 if ((sh->envp[j] = ft_strdup(envp[j])) == NULL)
		 {
		 	log_fatal("ft_strdup failded because of insuffisant memory availale");
		 	return (-ST_MALLOC);
		 }
//		ft_putendl_fd(sh->envp[j], 1);
		j++;
	}
	return (ST_OK);
}
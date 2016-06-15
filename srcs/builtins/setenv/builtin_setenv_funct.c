#include "shell.h"

static	int		s_concat_variable(char **str, char *key, char *value)
{
	char		*tmp;
	char		*tmp2;
//CHECK DES RETURN ST_MALLOC
	tmp = ft_strjoin(key, "=");
	if (!value)
	{
		*str = ft_strdup(tmp);
		free(tmp);	
	}
	else if (value)
	{
		tmp2 = ft_strjoin(tmp, value);
		free(tmp);
		*str = ft_strdup(tmp2);
		free(tmp2);
	}
	return (ST_OK);
}

static	char	**s_env_set_new_variable(t_sh *sh, char *variable, char *value)
{
	char		**tmp;
	int			i;
	int			size;
//CHECK DES RETURN ST_MALLOC
	i = 0;
	size = 0;
	tmp = NULL;
	while (sh->envp[size])
		size++;
	tmp = (char **)malloc(sizeof(char *) * (size + 2));
	while (sh->envp[i] != NULL)
	{
		tmp[i] = ft_strdup(sh->envp[i]);
		i++;
	}
	s_concat_variable(&(tmp[i]), variable, value);
	i++;
	tmp[i] = NULL;
	ft_memdel_tab((void ***)&sh->envp);
	return (tmp);
}

int				env_index_value(t_sh *sh, char *variable)
{
	int			i;
	int			size;

	i = 0;
	size = ft_strlen(variable);
	while (sh->envp[i])
	{
		if (ft_strncmp(sh->envp[i], variable, size) == 0)
		{
			if (!sh->envp[i][size])
				return (-1);
			else if (sh->envp[i][size] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

int				setenv_set_variable_and_value(t_sh *sh, t_proc *p)
{
	int			i;
	int			ret;

	i = 0;
	if ((ret = env_index_value(sh, p->argv[1])) == -1)
		sh->envp = s_env_set_new_variable(sh, p->argv[1], p->argv[2]);
	else
	{
		if (!p->argv[2])
			s_concat_variable(&sh->envp[ret], p->argv[1], NULL);
		else if (p->argv[2])
			s_concat_variable(&sh->envp[ret], p->argv[1], p->argv[2]);
	}
	return (ST_OK); //check other function return
}

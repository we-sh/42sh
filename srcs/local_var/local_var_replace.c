#include "shell.h"

int		local_var_replace_recursive(char **argv, t_sh *sh, int i)
{
	int	j;
	int	k;
	int	z;
	char **tab;
	t_var *ptr;

	j = 0;
	k = 0;
	z = 0;
	while (argv[i][j] != '$' && argv[i][j] != '\0')
		j++;
	if (j == (int)ft_strlen(argv[i]))
		return (ST_OK);


	tab = ft_strsplit(argv[i], '$');
	while (tab[z])
	{
		log_info("TAB[%d]->%s", z, tab[z]);
		ptr = sh->local_vars;
		while (ptr)
		{
			log_success("BROWSE PTR");
			if (ft_strcmp(tab[z], ptr->key) == 0)
			{
				free(tab[z]);
				tab[z] = ft_strdup(ptr->value);
			}
			ptr = ptr->next;
		}
		log_success("TAB[%d]->%s", z, tab[z]);
		z++;
	}

	char *tmp;
	char *tmp2;

	tmp = NULL;
	z = 0;
	while (tab[z])
	{
		if (tmp == NULL)
			tmp = ft_strdup(tab[z]);
		else
		{
			tmp2 = ft_strjoin(tmp, tab[z]);
			free(tmp);
			tmp = ft_strdup(tmp2);
			free(tmp2);
		}
		z++;
	}
	free(argv[i]);
	argv[i] = ft_strdup(tmp);
	free(tmp);
	return (ST_OK);
}

int		local_var_replace(char **argv, t_sh *sh)
{
	int	i;
	t_var	*ptr;
	char *tmp;

	ptr = sh->local_vars;
	i = 0;
	tmp = NULL;
	while (argv[i])
	{
		log_warn("Value of ARGV[%d] %s",i , argv[i]);
		local_var_replace_recursive(argv, sh, i);
		i++;
	}
	return (ST_OK);
}
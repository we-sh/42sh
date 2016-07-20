#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the local variable struc if no binary are found.
*/

static int s_local_is_valid(t_sh *sh, t_job **j, int *i)
{
	char	**test;
	char	*value;

	test = ft_strsplit((*j)->command, ' ');
	while (test[*i] != '\0')
	{
		if (path_hash_finder(sh->envp, &test[*i]) == ST_OK)
			return (-1);
		if ((value = env_get_value_and_remove_equal_sign(test[*i])) == NULL)
			return (-1);
		*i += 1;
	}
	ft_memdel_tab((void ***)&test);
	return (0);
}

int			local_var_insert(t_sh **sh, t_job **j)
{
	char	*tmp;
	int		i;

	i = 0;
	if (s_local_is_valid(*sh, j, &i) != ST_OK)
		return (ST_OK);
	tmp = ft_strdup((*j)->command);
	ft_memdel((void **)&((*j)->command));
	(*j)->command = ft_strjoin("setlocal ", tmp);
	return (0);
}

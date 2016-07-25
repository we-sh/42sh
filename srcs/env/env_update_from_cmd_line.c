#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the local variable struc if no binary are found.
*/

// static int			local_var_insert(char *argv)
// {
// 	char	*tmp;

// 	if ()
// 		return (ST_OK);
// 	tmp = ft_strdup(argv);
// 	ft_memdel((void **)&(argv);
// 	(*j)->command = ft_strjoin("setlocal ", tmp);
// 	return (0);
// }

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the specified environment.
*/

int			env_update_from_cmd_line(char ***argv, int *argc, char ***envp)
{
	char	*value;
	char 	**tmptab;
	int		ret;
	int		add_to_env;
	int		nbr;
	int		i;
	int		flag = 0;

	i= 0;
	if (!argv)
		return (ST_OK);
	add_to_env = 0;
	nbr = *argc;
	tmptab = NULL;
	tmptab = (char **)malloc(sizeof(char *)* (*argc + 1));
	while (nbr > 0 && (*argv)[0] != NULL && (*argv)[0][0] != '\0')
	{
		if (*argv[0] && ft_strcmp(*argv[0], "env") == 0)
			add_to_env = 1;
		tmptab[i] = ft_strdup(*argv[0]);
		i++;
		ft_array_pop(argv, 0, 1);
		nbr--;
	}
	tmptab[i] = NULL;

	char **test;
	test = (char **)malloc(sizeof(char *)* (*argc + 1));;
	i = 0;
	while (tmptab[i])
	{
		log_info("valeur de tmp %s" ,tmptab[i]);
		test[i] = ft_strdup(tmptab[i]);
		i++;
	}
	test[i] = NULL;
	//*argv = tmptab;
	i = 0;
	if (add_to_env == 0)
	{
		while (test[i] != NULL && test[i][0] != '\0' && test[i][0] != '=')
		{
		log_success("check SIGN nbr : %d, value %s", nbr, test[i]);
			if ((value = env_get_value_and_remove_equal_sign(test[i])) != NULL)
				flag = 1;
			else
			{
				flag = 0;
				break ;
			}
		i++;
		}

		log_success("Value of argc %d, flag = %d", *argc, flag);
	//	ft_array_pop(&tmptab, 0, 1);
//		*argc += 1;
	}
	else
	{
		while (tmptab[0] != NULL && tmptab[0][0] != '\0' && tmptab[0][0] != '='
			&& (value = env_get_value_and_remove_equal_sign(tmptab[0])) != NULL)
		{
			if (envp != NULL)
				if ((ret = env_set(envp, tmptab[0], value)) != ST_OK)
					return (ret);
			*argc -= 1;
			ft_array_pop(&tmptab, 0, 1);
		}
	}
	if (flag == 1)
	{
		ft_array_push_front(&tmptab, "setlocal");
		*argc += 1;
	}
	i = 0;
	while (tmptab[i])
	{
		log_info("valeur de tmp %s" ,tmptab[i]);
		i++;
	}
		log_success("Out 1");
	*argv = tmptab;
		log_success("Out 2 ");
	return (ST_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update_from_cmd_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function may pop all valid variables placed at start of a command
** line and set them into the specified environment.
*/

static char	*s_get_value_and_remove_equal_sign(char *arg)
{
	char	*equal_sign;

	if ((equal_sign = ft_strstr(arg, "=")) != NULL)
	{
		arg[equal_sign - arg] = '\0';
		if (setenv_argv_is_valid(arg) == ST_OK)
			return (equal_sign + 1);
	}
	return (NULL);
}

int			env_update_from_cmd_line(char ***argv, int *argc, char ***envp)
{
	char	*value;
	int		ret;

	if (!argv)
		return (ST_OK);
	while ((*argv)[0] != NULL && (*argv)[0][0] != '\0' && (*argv)[0][0] != '='
		&& (value = s_get_value_and_remove_equal_sign((*argv)[0])) != NULL)
	{
		if (envp != NULL)
			if ((ret = env_set(envp, (*argv)[0], value)) != ST_OK)
				return (ret);
		*argc -= 1;
		ft_array_pop(argv, 0, 1);
	}
	return (ST_OK);
}

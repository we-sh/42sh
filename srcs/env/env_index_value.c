/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_index_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				env_index_value(char **envp, char *variable)
{
	int			i;
	int			size;

	i = 0;
	size = ft_strlen(variable);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], variable, size) == 0)
		{
			if (!envp[i][size])
				return (-1);
			else if (envp[i][size] == '=')
				return (i);
		}
		i++;
	}
	return (-1);
}

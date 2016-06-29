/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*env_get_term(char **envp)
{
	char			*tmp;
	char			*bd;

	bd = NULL;
	if ((tmp = env_get(envp, "TERM")) == NULL)
	{
		if (!tgetent(bd, "xterm"))
		{
			log_fatal("tgetent() failed termtype xterm");
			return (NULL);
		}
		else
			tmp = "xterm";
	}
	return (tmp);
}

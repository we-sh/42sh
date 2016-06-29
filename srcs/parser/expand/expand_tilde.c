/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Tilde `~` must be the first expansion to perform.
*/

int			expand_tilde(t_globing_param *params, t_lexer *lexer, int *i)
{
	char	*tmp;
	char	*output;

	log_debug("expanding tilde");
	output = input;
	if (input[0] == '~')
	{
		tmp = env_get_home(sh->envp);
		if (tmp)
		{
			output = ft_strjoin(tmp, input + 1);
			ft_memdel((void **)&input);
		}
	}
	return (output);
}

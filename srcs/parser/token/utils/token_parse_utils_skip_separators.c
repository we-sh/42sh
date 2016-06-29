/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils_skip_separators.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function iterates on tokens while a separator is encountered
** If the argument `char **command` is set, separators are pushed
*/

int			token_parse_utils_skip_separators(t_lexer *lexer, int *i,
				char **command)
{
	int		ret;

	while (*i < lexer->size && TOKEN_TYPE(*i) == TT_SEPARATOR)
	{
		if (command)
		{
			ret = token_parse_utils_push_command(TOKEN_CONTENT(*i), command);
			if (ret != ST_OK)
				return (ret);
		}
		(*i)++;
	}
	return (ST_OK);
}

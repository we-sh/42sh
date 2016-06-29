/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_build_list_unstack_lexer.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** For each token of the lexer, apply a function and build a 'job-tree' into the
** global variable g_current_jobs_list_head.
*/

int			parser_build_list_unstack_lexer(t_parser *parser)
{
	int		i;
	int		ret;

	if (!parser)
		return (ST_EINVAL);
	i = 0;
	while (i < parser->lexer->size)
	{
		if ((ret = parser->unstack_func(parser, parser->lexer, &i)) != ST_OK)
			return (ret);
	}
	return (ST_OK);
}

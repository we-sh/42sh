/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Convert an input string into a token list.
*/

int			lexer(t_parser *parser, const char *in)
{
	int		ret;

	if (!parser || !in)
		return (ST_EINVAL);
	if ((ret = lexer_tokenize(in, parser, parser->lexer)) != ST_OK)
		return (ret);
	return (ST_OK);
}

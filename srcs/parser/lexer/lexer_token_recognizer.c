/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_recognizer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token			*lexer_token_recognizer(t_parser *parser, const char *s, int i)
{
	int			is_escaped;
	int			l;

	if (i > 0)
	{
		l = 0;
		is_escaped = 0;
		while (i - l > 0)
		{
			l++;
			if (*(s - l) != '\\')
				break ;
			is_escaped = is_escaped == 1 ? 0 : 1;
		}
		if (is_escaped == 1)
			return (NULL);
	}
	l = -1;
	while (parser->token_list[++l])
		if (ft_strncmp(s, parser->token_list[l]->op,
			parser->token_list[l]->len) == 0)
			return (parser->token_list[l]);
	return (NULL);
}

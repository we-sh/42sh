/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_bufferize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		lexer_bufferize(t_lexer *lexer, const char *str, int len)
{
	char		*tmp;

	if (lexer->buf_index + len >= lexer->buf_allocated_size)
	{
		tmp = lexer->buf;
		lexer->buf_allocated_size = lexer->buf_index + len\
													+ TOKEN_BUFFER_REALLOC;
		lexer->buf = ft_strnew(lexer->buf_index + len + TOKEN_BUFFER_REALLOC);
		if (lexer->buf == NULL)
			return (ST_MALLOC);
		lexer->buf = ft_strcpy(lexer->buf, tmp);
		free(tmp);
	}
	ft_strncat(lexer->buf, str, len);
	lexer->buf_index += len;
	return (ST_OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens_realloc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				lexer_tokens_realloc(t_lexer *lexer)
{
	t_token		**new_token_list;
	int			i;
	int			size;

	if (lexer->size + 1 >= lexer->allocated_size)
	{
		lexer->allocated_size += TOKEN_LIST_REALLOC;
		size = sizeof(t_token *) * (lexer->allocated_size);
		if ((new_token_list = (t_token **)malloc(size)) == NULL)
			return (ST_MALLOC);
		i = 0;
		while (i < lexer->size)
		{
			new_token_list[i] = lexer->tokens[i];
			i++;
		}
		while (i < lexer->allocated_size)
		{
			new_token_list[i] = NULL;
			i++;
		}
		free(lexer->tokens);
		lexer->tokens = new_token_list;
	}
	return (ST_OK);
}

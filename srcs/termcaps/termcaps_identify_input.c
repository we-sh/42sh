/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_identify_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		termcaps_identify_input(const unsigned int c,
										t_input_type *input_type,
										size_t *input_size_missing)
{
	size_t	character_size;

	*input_type = MINISHELL__INPUT_TYPE_UNDEFINED;
	*input_size_missing = 0;
	if (ft_isprint(c))
	{
		*input_type = MINISHELL__INPUT_TYPE_PRINT;
	}
	else if (termcaps_isunicode(c, &character_size))
	{
		*input_type = MINISHELL__INPUT_TYPE_UNICODE;
		*input_size_missing = character_size;
	}
	else
	{
		*input_type = MINISHELL__INPUT_TYPE_CAPS;
		if (c == '\x1b')
			*input_size_missing = INPUT_SIZE_MAX - 1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__cursor_to_next_character.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__cursor_to_next_character(t_termcaps_context *in_context)
{
	if (in_context->command_line.offset == in_context->command_line.size)
		return (1);
	in_context->command_line.offset += 1;
	return (1);
}

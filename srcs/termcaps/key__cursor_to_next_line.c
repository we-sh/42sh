/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__cursor_to_next_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__cursor_to_next_line(t_termcaps_context *in_context)
{
	int	distance;

	distance = in_context->command_line.offset + caps__win(WIN_COLUMNS);
	if (distance < (int)in_context->command_line.size)
		in_context->command_line.offset = distance;
	else
		in_context->command_line.offset = in_context->command_line.size;
	return (1);
}

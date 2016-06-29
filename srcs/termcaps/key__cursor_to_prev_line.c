/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__cursor_to_prev_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__cursor_to_prev_line(t_termcaps_context *context)
{
	int	distance;

	distance = context->command_line.offset - caps__win(WIN_COLUMNS);
	if (distance > (int)context->prompt.size)
		context->command_line.offset = distance;
	else
		context->command_line.offset = context->prompt.size;
	return (1);
}

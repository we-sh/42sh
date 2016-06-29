/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__cut_to_end_of_line.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			key__cut_to_end_of_line(t_termcaps_context *in_context)
{
	size_t	selection_start;
	size_t	selection_end;

	if (in_context->state != STATE_REGULAR)
		return (1);
	selection_start = in_context->command_line.offset;
	selection_end =
		in_context->command_line.size - in_context->command_line.offset;
	key__share__cut_build_copy(in_context,
								selection_start,
								selection_end);
	return (1);
}

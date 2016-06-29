/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__select(t_termcaps_context *in_context)
{
	if (in_context->state == STATE_REGULAR)
	{
		ft_putstr(SELECTBLEU);
		in_context->state = STATE_SELECTION;
		in_context->selection_offset_start = in_context->command_line.offset;
		in_context->selection_offset_end =
			MINISHELL_KEY__SHARE__SELECTION_OFFSET_UNDEFINED;
	}
	else if (in_context->state == STATE_SELECTION)
	{
		ft_putstr(SELECTBLANC);
		in_context->state = STATE_REGULAR;
		if (in_context->command_line.offset >
			in_context->selection_offset_start)
			in_context->selection_offset_end = in_context->command_line.offset;
		else
		{
			in_context->selection_offset_end =
			in_context->selection_offset_start;
			in_context->selection_offset_start =
			in_context->command_line.offset;
		}
	}
	return (1);
}

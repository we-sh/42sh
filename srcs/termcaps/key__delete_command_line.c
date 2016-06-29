/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__delete_command_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		s_key_delete_selection(t_termcaps_context *context)
{
	t_list_head	head;
	size_t		selection_start;
	size_t		selection_size;

	ft_putstr(SELECTBLANC);
	context->state = STATE_REGULAR;
	key__share__selection_get(context, &selection_start, &selection_size);
	list_head__init(&head);
	list_head__slice(&head, &context->command_line,
					selection_start, selection_size);
	list_head__command_line_destroy(&head);
	context->command_line.offset = selection_start;
	return (ST_OK);
}

int				key__delete_command_line(t_termcaps_context *context)
{
	if (context->state == STATE_REGULAR)
	{
		list_head__command_line_destroy(&context->command_line);
		list_head__init(&context->command_line);
		context->command_line.offset = 0;
		if (!termcaps_string_to_command_line(context->prompt.size,
											context->prompt.bytes,
											&context->command_line))
		{
			log_error("minishell__string_to_command_line() failed %.*s",
				(int)context->prompt.size, context->prompt.bytes);
			return (0);
		}
		context->history.offset = context->history.size;
	}
	else if (context->state == STATE_SELECTION)
		s_key_delete_selection(context);
	return (1);
}

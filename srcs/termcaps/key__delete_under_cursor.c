/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__delete_under_cursor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__delete_under_cursor(t_termcaps_context *context)
{
	t_list *entry;

	if (context->state == STATE_REGULAR)
	{
		if (context->command_line.size == context->prompt.size &&
				context->option == OPTION_NONE)
		{
			context->buffer = ft_strdup("exit");
			return (1);
		}
		if (context->command_line.offset == context->command_line.size)
			return (1);
		entry = list_nth(&context->command_line.list,
					context->command_line.offset + 1);
		list_head__del(&context->command_line, entry);
		list_node__command_line_destroy(entry);
	}
	else if (context->state == STATE_SEARCH_HISTORY)
	{
		context->state = STATE_REGULAR;
		context->history.offset = context->history.size;
	}
	return (1);
}

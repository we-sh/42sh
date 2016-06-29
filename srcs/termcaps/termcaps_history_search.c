/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_history_search.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int				s_termcaps_history_search_loop(
													t_termcaps_context *context,
													t_buffer *out_match,
													char *command_line_cur)
{
	t_list				*pos;
	t_list_node_history	*history;
	size_t				history_offset;

	history_offset = context->history.offset;
	pos = list_nth(&context->history.list, history_offset + 1);
	while ((pos = pos->prev) && pos != &context->history.list)
	{
		history = CONTAINER_OF(pos, t_list_node_history, list);
		if (ft_strstr(history->command_line.bytes,
					command_line_cur +
					context->prompt.size))
		{
			out_match->size = history->command_line.size;
			out_match->bytes = history->command_line.bytes;
			context->history.offset = history_offset;
			return (1);
		}
		history_offset--;
	}
	return (0);
}

int						termcaps_history_search(t_termcaps_context *context,
												t_buffer *out_match)
{
	char				command_line_cur[TERMCAPS_BUFFER_MAX];
	size_t				command_line_cur_size;

	out_match->size = 0;
	out_match->bytes = NULL;
	if (context->command_line.size > context->prompt.size)
	{
		ASSERT(list_head__command_line_to_buffer(&context->command_line,
												sizeof(command_line_cur) - 1,
												&command_line_cur_size,
												command_line_cur));
		command_line_cur[command_line_cur_size] = 0;
		if ((s_termcaps_history_search_loop(context,
											out_match,
											command_line_cur)) == 1)
			return (1);
	}
	return (0);
}

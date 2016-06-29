/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				key__paste(t_termcaps_context *in_context)
{
	t_list		*pos;
	t_list_head	dup;

	if (in_context->state != STATE_REGULAR)
		return (1);
	pos = list_nth(&in_context->command_line.list,
					in_context->command_line.offset);
	list_head__command_line_dup(&dup, &in_context->copy);
	list_splice(&dup.list, pos);
	in_context->command_line.size += dup.size;
	in_context->command_line.offset += dup.size;
	return (1);
}

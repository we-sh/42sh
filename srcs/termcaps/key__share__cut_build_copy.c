/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__share__cut_build_copy.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					key__share__cut_build_copy(
											t_termcaps_context *in_context,
											size_t selection_start,
											size_t selection_size)
{
	list_head__command_line_destroy(&in_context->copy);
	list_head__init(&in_context->copy);
	list_head__slice(&in_context->copy,
					&in_context->command_line,
					selection_start,
					selection_size);
	in_context->command_line.offset = selection_start;
}

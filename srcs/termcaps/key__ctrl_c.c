/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__ctrl_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__ctrl_c(t_termcaps_context *context)
{
	if (context->state != STATE_REGULAR)
		return (1);
	ASSERT(termcaps_display_command_line(context));
	list_head__command_line_destroy(&context->command_line);
	list_head__init(&context->command_line);
	context->buffer = ft_strdup("^C\n");
	return (1);
}

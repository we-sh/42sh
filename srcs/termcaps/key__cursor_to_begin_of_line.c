/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__cursor_to_begin_of_line.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__cursor_to_begin_of_line(t_termcaps_context *context)
{
	context->command_line.offset = context->prompt.size;
	return (1);
}

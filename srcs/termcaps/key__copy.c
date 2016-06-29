/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__copy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			key__copy(t_termcaps_context *in_context)
{
	size_t	copy_start;
	size_t	copy_size;

	if (in_context->state != STATE_SELECTION)
		return (1);
	ft_putstr(SELECTBLANC);
	in_context->state = STATE_REGULAR;
	ASSERT(key__share__selection_get(in_context, &copy_start, &copy_size));
	ASSERT(key__share__copy_build_copy(&in_context->command_line,
										copy_start,
										copy_size,
										&in_context->copy));
	return (1);
}

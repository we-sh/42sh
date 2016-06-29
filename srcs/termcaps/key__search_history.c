/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__search_history.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "list_head.h"

int	key__search_history(t_termcaps_context *context)
{
	if (context->state == STATE_SEARCH_HISTORY)
	{
		if (context->history.offset > 0)
			context->history.offset--;
	}
	else
	{
		context->state = STATE_SEARCH_HISTORY;
	}
	return (1);
}

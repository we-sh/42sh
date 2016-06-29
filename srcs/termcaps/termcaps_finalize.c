/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_finalize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		termcaps_finalize(t_termcaps_context *context)
{
	list_head__history_destroy(&context->history);
	list_head__command_line_destroy(&context->command_line);
	list_head__command_line_destroy(&context->copy);
	free(context->prompt.bytes);
	context->is_initialized = 0;
	return (1);
}

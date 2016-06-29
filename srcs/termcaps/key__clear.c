/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		key__clear(t_termcaps_context *context)
{
	(void)context;
	caps__print_cap(CAPS__HOME_CLEAR, caps__win(WIN_LINE));
	return (1);
}

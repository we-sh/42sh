/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils_open_new_fd.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			token_parse_utils_open_new_fd(t_proc *p, char *f, int *fd, int flag)
{
	if ((*fd = open(f, flag, 0644)) < 0)
	{
		display_status(ST_OPEN, f, NULL);
		p->is_valid = -1;
	}
	return (ST_OK);
}

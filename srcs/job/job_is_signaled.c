/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_is_signaled.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** This function returns 1 if the given job t_job has at least on signaled proc.
*/

int	job_is_signaled(t_job *j)
{
	t_list		*head;
	t_list		*pos;
	t_proc		*p;

	head = &j->proc_head;
	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		p = CONTAINER_OF(pos, t_proc, list_proc);
		if (p->signaled != 0)
			return (p->signaled);
	}
	return (0);
}

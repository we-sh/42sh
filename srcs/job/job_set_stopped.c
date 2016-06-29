/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_set_stopped.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	job_set_stopped(t_job *j, int const stopped)
{
	t_list	*p_pos;
	t_proc	*p;

	p_pos = &j->proc_head;
	while ((p_pos = p_pos->next) && p_pos != &j->proc_head)
	{
		p = CONTAINER_OF(p_pos, t_proc, list_proc);
		p->stopped = stopped;
	}
}

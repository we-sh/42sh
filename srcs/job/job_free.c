/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	job_free(t_job **j)
{
	t_proc	*p;
	t_list	*pos;
	t_list	*safe;
	t_list	*head;

	head = &(*j)->proc_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		p = CONTAINER_OF(pos, t_proc, list_proc);
		proc_free(&p);
	}
	ft_memdel((void **)&(*j)->command);
	ft_memdel((void **)&(*j));
	*j = NULL;
}

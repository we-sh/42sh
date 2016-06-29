/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_by_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job	*job_by_id(int const id, int const foreground)
{
	t_list	*j_pos;
	t_job	*j;

	j_pos = &g_current_jobs_list_head;
	while ((j_pos = j_pos->next) && j_pos != &g_current_jobs_list_head)
	{
		j = CONTAINER_OF(j_pos, t_job, list_job);
		if (j->foreground == foreground)
			if (j->id == id)
				return (j);
	}
	return (NULL);
}

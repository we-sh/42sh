/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_free_hasht.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			path_free_hasht(void)
{
	int			i;
	t_hasht		*tmp;

	i = 0;
	while (i < 5000)
	{
		tmp = NULL;
		while (bodies[i].head)
		{
			tmp = bodies[i].head->next;
			free(bodies[i].head->path);
			free(bodies[i].head->name);
			free(bodies[i].head);
			bodies[i].head = tmp;
		}
		i++;
	}
}

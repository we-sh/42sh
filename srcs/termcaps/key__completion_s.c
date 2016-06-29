/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key__completion_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_node_dir		*node_dir__create(const char *filename)
{
	void		*addr;
	t_node_dir	*new;
	size_t		filename_size;

	filename_size = ft_strlen(filename);
	addr = malloc(sizeof(t_node_dir) + filename_size + 1);
	if (!addr)
		return (NULL);
	new = addr;
	new->filename.bytes = addr + sizeof(t_node_dir);
	new->filename.size = filename_size;
	ft_memcpy(new->filename.bytes, filename, filename_size + 1);
	return (new);
}

void			list_dir__destroy(t_list *head)
{
	t_list		*pos;
	t_list		*safe;
	t_node_dir	*node_dir;

	safe = head->next;
	while ((pos = safe) && (pos != head))
	{
		safe = safe->next;
		node_dir = CONTAINER_OF(pos, t_node_dir, list);
		free(node_dir);
	}
}

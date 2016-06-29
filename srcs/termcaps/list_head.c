/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** list head
*/

void	list_head__insert(t_list_head *head, size_t offset, t_list *new)
{
	list_insert(new, &head->list, offset);
	head->size += 1;
	head->offset += 1;
}

void	list_head__del(t_list_head *head, t_list *entry)
{
	list_del(entry);
	head->size -= 1;
}

void	list_head__init(t_list_head *head)
{
	head->size = 0;
	head->offset = 0;
	INIT_LIST_HEAD(&head->list);
}

void	list_head__slice(t_list_head *new,
						t_list_head *head,
						size_t start,
						size_t len)
{
	list_slice(&new->list, &head->list, start, len);
	new->size += len;
	head->size -= len;
}

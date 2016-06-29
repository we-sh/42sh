/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		redir_list_free(t_list *redir_head)
{
	t_list	*head;
	t_list	*safe;
	t_list	*pos;
	t_redir	*redir;

	log_error("freeing list of fds");
	head = redir_head;
	safe = head->next;
	while ((pos = safe) && pos != head)
	{
		safe = safe->next;
		redir = CONTAINER_OF(pos, t_redir, list_redir);
		pos->prev->next = safe;
		safe->prev = pos->prev;
		redir_free(&redir);
	}
}

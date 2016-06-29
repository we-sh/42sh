/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_character_to_command_line.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Add a character to the current command line
*/

int		termcaps_character_to_command_line(const size_t character_bytes_count,
											const char *character_bytes,
											t_list_head *command_line)
{
	t_list_node_cmd	*new;

	new = list_node__command_line_create(character_bytes_count,
										character_bytes);
	if (!new)
	{
		log_error("list_node__command_line_create() failed bytes_count %zu",
			character_bytes_count);
		return (0);
	}
	list_head__insert(command_line,
						command_line->offset,
						&new->list);
	return (1);
}

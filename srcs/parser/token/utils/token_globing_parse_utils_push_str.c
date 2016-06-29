/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_globing_parse_utils_push_str.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			token_globing_parse_utils_push_str(t_list *head, char *str)
{
	t_list	*pos;
	t_argv	*argument;
	char	*tmp;

	pos = head;
	while ((pos = pos->next) && pos != head)
	{
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		tmp = argument->buffer;
		if ((argument->buffer = ft_strjoin(argument->buffer, str)) == NULL)
			return (ST_MALLOC);
		free(tmp);
	}
	return (ST_OK);
}

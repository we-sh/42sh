/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parse_utils_check_char_to_fd.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** Check whether the char * is the value 0, 1 or 2, and if so, set the fd
** pointer given in parameter. If the string doesn't statisfy the condition,
** the file descriptor is unchanged and the function returns ST_PARSER.
*/

int		token_parse_utils_check_char_to_fd(char *f, int *fd)
{
	int	open_fd;

	if ((ft_strisnumeric(f)) == 0)
		return (ST_PARSER);
	else
	{
		open_fd = ft_atoi(f);
		if (open_fd != STDIN_FILENO && open_fd != STDOUT_FILENO
				&& open_fd != STDERR_FILENO)
			return (ST_PARSER);
		*fd = open_fd;
	}
	return (ST_OK);
}

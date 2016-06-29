/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

/*
** The Shell may keep a list of opened file descriptors to distribute to its
** child during the two phase of parsing ST_PARSING_PROCS.
** File descriptors may be opened during the phase ST_PARSING_NONE and closed
** at each call of the parser in ST_PARSING_NONE mode.
*/

typedef struct			s_redir
{
	t_list				list_redir;
	int					fd;
}						t_redir;

#endif

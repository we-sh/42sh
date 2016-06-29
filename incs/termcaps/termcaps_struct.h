/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abombard <abombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by abombard          #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by abombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_STRUCT_H
# define TERMCAPS_STRUCT_H

# include "list_head.h"
# include "types.h"

typedef struct s_sh	t_sh;

/*
** termcaps context
*/
typedef struct	s_termcaps_context
{
	int										is_initialized;

	enum {
		STATE_REGULAR,
		STATE_SELECTION,
		STATE_SEARCH_HISTORY,
	}										state;

	enum {
		OPTION_NONE,
		OPTION_QUOTING,
		OPTION_HEREDOC
	}										option;

	struct termios							termios_old;
	struct termios							termios_new;

	int										fd;

	t_buffer								prompt;

	t_list_head								command_line;

	size_t									selection_offset_start;
	size_t									selection_offset_end;

	t_list_head								copy;

	t_list_head								history;

	char									*buffer;

	t_sh									*sh;
}				t_termcaps_context;

#endif

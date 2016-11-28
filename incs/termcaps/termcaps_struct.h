#ifndef TERMCAPS_STRUCT_H
# define TERMCAPS_STRUCT_H

# include "list_head.h"
# include "types.h"
# include "shell_struct.h"

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

	t_list_head								command;

	size_t									selection_offset_start;
	size_t									selection_offset_end;

	t_list_head								copy;

	char									history_file[255];
	t_list_head								history;
	size_t									history_initial_size;

	char									*buffer;

	t_sh									*sh;

	int										child;
}				t_termcaps_context;

#endif

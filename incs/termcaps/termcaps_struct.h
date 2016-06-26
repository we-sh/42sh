#ifndef TERMCAPS_STRUCT_H
# define TERMCAPS_STRUCT_H

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
		STATE_QUOTING,
		STATE_HEREDOC
	}										state;

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
	
	//char									*checkparse;

	t_sh									*sh;

	int										is_heredoc;
}				t_termcaps_context;


#endif /* TERMCAPS_STRUCT_H */

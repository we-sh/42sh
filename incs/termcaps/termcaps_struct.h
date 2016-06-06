#ifndef TERMCAPS_STRUCT_H
# define TERMCAPS_STRUCT_H

/*
** Internal context
*/
typedef struct	s_internal_context
{
	enum {
		STATE_REGULAR,
		STATE_SELECTION,
		STATE_CONTINUE,
		STATE_EXIT
	}										state;

	int										fd;
	t_buffer								prompt;

	char									*buffer;

	t_list_head								command_line;

	size_t									selection_offset_start;
	size_t									selection_offset_end;

	t_list_head								copy;

	t_list_head								history;
}				t_internal_context;


#endif /* TERMCAPS_STRUCT_H */

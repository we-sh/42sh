#ifndef KEY_H
# define KEY_H

/*
** -- Shared functions -- /\*
*/

/*
** Feed command line
*/
int	key__share__feed_command_line(const size_t input_buffer_size, const char *input_buffer, t_termcaps_context *in_context);

/*
** Command line to history
*/
int	key__share__command_line_to_history(t_termcaps_context *in_context);

/*
** Selection get
*/
int	key__share__selection_get(t_termcaps_context *in_context, size_t *out_selection_start, size_t *out_selection_size);

/*
** PREV / NEXT word offset
*/
void	key__share__prev_word_offset(const t_list_head *command_line, size_t current_offset, size_t prompt_size, size_t *out_offset);
void	key__share__next_word_offset(const t_list_head *command_line, size_t current_offset, size_t *out_offset);

/*
** Copy build copy
*/
int	key__share__copy_build_copy(t_list_head *command_line, size_t copy_start, size_t copy_size, t_list_head *out_copy);

/*
** Cut build copy
*/
void	key__share__cut_build_copy(t_termcaps_context *in_context, size_t selection_start, size_t selection_size);


/*
** -- Keys -- /\*
*/

/*
** Select
*/
int	key__select(t_termcaps_context *in_context);

/*
** Delete command line
*/
int	key__delete_command_line(t_termcaps_context *in_context);

/*
** Send
*/
int	key__send(t_termcaps_context *in_context);

/*
** Backspace
*/
int	key__backspace(t_termcaps_context *in_context);

/*
** delete character under cursor
*/
int	key__delete_under_cursor(t_termcaps_context *in_context);

/*
** Cursor to PREV / NEXT character
*/
int	key__cursor_to_prev_character(t_termcaps_context *in_context);
int	key__cursor_to_next_character(t_termcaps_context *in_context);

/*
** Cursor to PREV / NEXT word
*/
int	key__cursor_to_prev_word(t_termcaps_context *in_context);
int	key__cursor_to_next_word(t_termcaps_context *in_context);

/*
** Cursor to BEGIN / END of line
*/
int	key__cursor_to_begin_of_line(t_termcaps_context *in_context);
int	key__cursor_to_end_of_line(t_termcaps_context *in_context);

/*
** Cursor to NEXT / PREVIOUS line
*/
int	key__cursor_to_prev_line(t_termcaps_context *in_context);
int	key__cursor_to_next_line(t_termcaps_context *in_context);

/*
** Cursor to PREVIOUS / NEXT command
*/
int	key__cursor_to_prev_command(t_termcaps_context *in_context);
int	key__cursor_to_next_command(t_termcaps_context *in_context);

/*
** Copy
*/
int	key__copy(t_termcaps_context *in_context);

/*
** Cut
*/
int	key__cut(t_termcaps_context *in_context);
int	key__cut_to_end_of_line(t_termcaps_context *in_context);

/*
** Paste
*/
int	key__paste(t_termcaps_context *in_context);

/*
** Completion
*/
int	key__completion(t_termcaps_context *in_context);

/*
** Ctrl C
*/
int key__ctrl_c(t_termcaps_context *in_context);

/*
** Search history
*/
int key__search_history(t_termcaps_context *in_context);

/*
** Use for completion
*/
size_t		key__completion_list_dir(t_termcaps_context *context,
									t_list *head,
									t_buffer *match);


/*
** Clear
*/
int	key__clear(t_termcaps_context *in_context);

#endif /* KEY_H */

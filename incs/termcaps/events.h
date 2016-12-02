#ifndef EVENTS_H
# define EVENTS_H

# define EVENTS_COUNT_MAX	1000

# define WORD_ALL	 -42
# define WORD_ARGS	 -2

typedef struct	s_event
{
	size_t	token_size;
	int		history_index;
	int		word;
}				t_event;

int				replace_events(t_termcaps_context *context,
								const size_t buffer_size_max,
								t_buffer *buffer);
int				event_info(t_list_head *history,
							const char *pt,
							t_event *event);
int				event_word(t_event *info, t_buffer *event);
#endif

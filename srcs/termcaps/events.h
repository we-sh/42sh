#ifndef EVENTS_H
# define EVENTS_H

typedef struct	s_event
{
	char	*token;
	size_t	token_size;
	int		word;
	char	*event;
	size_t	event_size;
}				t_event;

#endif

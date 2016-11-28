#ifndef TERMCAPS_H
# define TERMCAPS_H

# include <termcap.h>
# include "list_head.h"
# include "log.h"
# include "termcaps_struct.h"
# include "key.h"

# define PROMPT_SIZE		(sizeof ("$> ") - 1)
# define PROMPT						 "$> "
# define MINISHELL_KEY__SHARE__SELECTION_OFFSET_UNDEFINED	(size_t)-1
# define INPUT_SIZE_MAX	7

/*
** Read and treat raw input
*/
typedef enum	e_input_type
{
	MINISHELL__INPUT_TYPE_UNDEFINED = 0,
	MINISHELL__INPUT_TYPE_PRINT,
	MINISHELL__INPUT_TYPE_UNICODE,
	MINISHELL__INPUT_TYPE_CAPS
}				t_input_type;

typedef enum	e_state_word
{
	STATE_UNDEFINED,
	STATE_ALNUM,
	STATE_ISSPACE
}				t_state_word;

/*
** completion
*/
typedef struct	s_node_dir
{
	char			filename[256];
	size_t			filename_size;
	unsigned char	d_type;
	t_list			list;
}				t_node_dir;

int				replace_events(t_termcaps_context *context,
								const size_t buffer_size_max,
								t_buffer *buffer);
int				event_info(t_list_head *history,
							const char *pt,
							size_t *token_size,
							int *history_index);
void			termcaps_error(t_termcaps_context *context,
							char *cmd, size_t cmd_size, char *msg);

int				history_init(t_termcaps_context *context);
int				history_filename(size_t size_max, char *filename);

#endif

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

/*
** inhibitors
** ' '
*/

# define TERMCAPS_INIB_COUNT	1

typedef struct	s_inib
{
	char	open;
	char	close;
	int		state;
}				t_inib;

void			termcaps_error(t_termcaps_context *context,
							char *cmd, size_t cmd_size, char *msg);

int				history_init(t_sh *sh);
int				history_get_filename(char **envp,
								size_t size_max, char *filename);

int				count_func(const char *s, int (*test)(int c), int expected);

#endif

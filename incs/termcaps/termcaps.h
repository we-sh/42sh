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
typedef enum {
	MINISHELL__INPUT_TYPE_UNDEFINED = 0,
	MINISHELL__INPUT_TYPE_PRINT,
	MINISHELL__INPUT_TYPE_UNICODE,
	MINISHELL__INPUT_TYPE_CAPS
} t_input_type;

#endif /* TERMCAPS_H */

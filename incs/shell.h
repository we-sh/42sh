#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "logger.h"
# include "types.h"
# include "statuses.h"
# include "get_next_line.h"

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>

/*
** Prompt statement default value
*/
# define PS1_DFLT "$ "

int	shell_init(void);
int	stdin_loop(void);

#endif

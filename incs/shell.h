#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "logger.h"
# include "types.h"
# include "job.h"
# include "statuses.h"
# include "i18n.h"
# include "get_next_line.h"

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>

/*
** Prompt statement default value
*/
# define PS1_DFLT "$ "

int		stdin_loop(void);
int		parse(char const *input);

/*
** i18n/
*/
char const	*i18n_translate(int status);

/*
** init/
*/
int		shell_fd(void);
int		shell_init(void);
int		shell_is_interactive(void);
int		shell_language(int lang);

/*
** job/
*/
int		job_launch(t_job *j);
void	proc_launch(t_job *j, t_proc *p);

#endif

#ifndef SHELL_H
# define SHELL_H

/*
** Extern headers and structures
*/
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
typedef struct termios		t_termios;

# include "libft.h"
# include "list.h"
# include "logger.h"
# include "job.h"
# include "statuses.h"
# include "i18n.h"
# include "get_next_line.h"

/*
** Prompt statement default value
*/
# define PS1_DFLT "$ "

/*
** List of current jobs
*/
t_list	g_current_jobs_list_head;

int		stdin_loop(void);
int		parse(char const *input);

/*
** exit/
*/
void	shell_exit(int status);

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
int		job_foreground(t_job *j, int sigcont);
int		job_is_completed(t_job *j);
int		job_launch(t_job *j);
t_proc	*proc_find(pid_t pid);
void	proc_launch(t_job *j, t_proc *p);
int		proc_update_status(pid_t pid, int status);
t_list	*list_node__proc_alloc(char **argv);
t_job	*job_alloc(char *command);

/*
** signal/
*/
void	signal_sigchld(int sig);
int		signal_to_ignore(void);
int		signal_to_default(void);

#endif

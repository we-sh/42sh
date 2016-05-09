#ifndef JOB_H
# define JOB_H

# include "types.h"

typedef struct				s_proc
{
	t_process				*next;
	char					**argv;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						status;
}							t_proc;

typedef struct				s_job
{
	t_job					*next;
	t_process				*proc;
	char					*command;
	pid_t					pgid;
	char					notified;
	t_termios				tmodes;
	int						stdin;
	int						stdout;
	int						stderr;
}							t_job;

#endif

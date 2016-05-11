#ifndef JOB_H
# define JOB_H

# include "types.h"

typedef struct				s_proc
{
	t_proc					*next;
	char					**argv;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						status;
	int						stdin;
	int						stdout;
	int						stderr;
}							t_proc;

typedef struct				s_job
{
	t_job					*next;
	t_proc					*proc;
	char					*command;
	pid_t					pgid;
	char					notified;
	t_termios				tmodes;
	int						foreground;
	int						stdin;
	int						stdout;
	int						stderr;
}							t_job;

#endif

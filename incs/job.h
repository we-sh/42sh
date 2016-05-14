#ifndef JOB_H
# define JOB_H

typedef struct				s_proc
{
	struct s_proc			*next;
	char					**argv;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						stdin;
	int						stdout;
	int						stderr;
	int						exit_status;
}							t_proc;

typedef struct				s_job
{
	struct s_job			*next;
	struct s_job			*prev;
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

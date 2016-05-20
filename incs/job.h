#ifndef JOB_H
# define JOB_H

typedef struct				s_proc
{
	t_list					list_proc;
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
	t_list					list_job;
	t_list					proc_head;
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

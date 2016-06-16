#ifndef JOB_H
# define JOB_H

typedef struct termios		t_termios;

typedef struct				s_proc
{
	t_list					list_proc;
	char					**argv;
	char					**envp;
	char					*command;
	int						argc;
	pid_t					pid;
	char					completed;
	char					stopped;
	char					signaled;
	int						stdin;
	int						stdout;
	int						stderr;
	int						exit_status;
	int						bltin_status;
	char					*bltin_char;
	t_list					bltin_opt_head;
	void					*j;
}							t_proc;

typedef struct				s_job
{
	t_list					list_job;
	t_list					proc_head;
	char					*command;
	pid_t					pgid;
	int						notified;
	t_termios				tmodes;
	int						foreground;
	int						launched;
	int						stdin;
	int						stdout;
	int						stderr;
	int						id;
}							t_job;

#endif

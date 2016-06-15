#ifndef JOB_H
# define JOB_H

typedef struct termios		t_termios;

/*
** A job may expected a success of the one before, an error or nothing.
*/
typedef enum	e_flag_job_wait
{
	F_WAIT_NO = 0,
	F_WAIT_SUCCESS,
	F_WAIT_ERROR
}				t_flag_job_wait;

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
	t_list					bltin_opt_head;
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
	int						stdin;
	int						stdout;
	int						stderr;
	int						id;

	t_flag_job_wait			wait;
}							t_job;

#endif

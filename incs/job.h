#ifndef JOB_H
# define JOB_H

typedef struct termios		t_termios;
typedef struct s_job		t_job;
typedef struct s_proc		t_proc;

/*
** A job may expected a success of the one before, an error or nothing.
*/
typedef enum				e_flag_job_separator
{
	F_JSEP_SEMI = 0,
	F_JSEP_AND_IF,
	F_JSEP_OR_IF
}							t_flag_job_separator;

/*
** Typedef to help code review in job_launch
*/
typedef enum				e_fds_job_launch
{
	FD_PIPE_IN = 0,
	FD_PIPE_OUT,
	FD_STDIN,
	FD_STDOUT,
	FD_STDERR
}							t_fds_job_launch;

struct						s_proc
{
	t_list					list_proc;
	t_job					*j;
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
	int						is_valid;
	int						is_subshell;
	int						pipe[2];
	t_sh					*sh;
};

struct						s_job
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
	int						exit_status;
	t_flag_job_separator	separator;
	int						is_interrupted;
};

#endif

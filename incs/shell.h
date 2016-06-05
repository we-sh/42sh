#ifndef SHELL_H
# define SHELL_H
# define TTY_DEVICE "/dev/tty"
# define PROGRAM_NAME "42sh"
# define PATH_MAX 4096
# define PATH_ROOT "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define PATH_STD "/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games"

/*
** Extern headers and structures
*/
# include <sys/types.h>
# include <sys/wait.h>
# include <pwd.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <curses.h>
# include <dirent.h>

/*
** Shell structure
*/

# include "list.h"

typedef struct		e_sh
{
	pid_t			pgid;
	bool			is_interactive;
	int				fd;
	char			**argv;
	char			**envp;
	struct termios	termios_old;
	struct termios	termios_new;
	int				last_exit_status;
	t_list			opt_head;
}					t_sh;

# include "libft.h"
# include "libftprintf.h"
# include "logger.h"
# include "statuses.h"
# include "option.h"
# include "job.h"
# include "termcaps.h"
# include "caps.h"
# include "i18n.h"
# include "get_next_line.h"
# include "lexer.h"
# include "builtin.h"

/*
** List of current jobs
*/
t_list		g_current_jobs_list_head;
typedef struct dirent	*t_dirent;

int				stdin_loop(t_sh *sh);
int				parse(t_sh *sh, char const *input);
int				environment_init(t_sh *sh, char **envp);

/*
** builtins/
*/
int				builtin_callback(int callback, t_sh *sh, t_proc *p);
int				setenv_argv_is_valid(t_proc *p);
void			builtin_usage(t_builtin const *bltin, int status);

/*
** env /
*/
char			*env_get(char **envp, char *key);
char			*env_get_path(char **envp);
char			*env_get_user(char **envp);
char			*env_get_home(char **envp);
char			*env_get_term(char **envp);
int				env_set(char ***envp, char *key, char *value);
int				env_unset(char ***envp, char *argv);
int				env_index_value(char **envp, char *variable);

/*
** log_status /
*/
int				display_status(const int status, const char *prefix, const char *suffix);

/*
** i18n/
*/
char const		*i18n_translate(int status);

/*
** init/
*/
//int				shell_fd(void);
int				shell_init(t_sh *sh);
int				shell_is_interactive(void);
int				shell_language(int lang);

/*
** job/
*/
int				job_available_id(void);
int				job_foreground(t_sh *sh, t_job *j, int const sigcont);
int				job_background(t_job *j, int const sigcont);
int				job_is_completed(t_job *j);
int				job_is_stopped(t_job *j);
int				job_launch(t_sh *sh, t_job *j);
t_proc			*proc_find(pid_t pid);
void			proc_launch(t_sh *sh, t_job *j, t_proc *p);
int				proc_update_status(pid_t pid, int status);
t_list			*list_node__proc_alloc(char *command, char **argv);
t_job			*job_alloc(char const *command);
int				job_wait(t_job *j);
int				job_kill(t_sh *sh, t_job *j, int status);
void			job_list_clean(int notified);
void			job_free(t_job **j);
void			proc_free(t_proc **p);
t_job			*job_by_name(char const *name);
t_job			*job_by_id(int const id);
t_job			*job_background_nth(const t_list *head, const int index);

/*
** options/
*/
int				option_is_set(t_list *list_option_head, int option_index);
char			*option_get_value(t_list *list_option_head, int option_index);
int				option_parse(t_list *list_head,
					t_option const **available_options,
					char ***argv, size_t start);
t_list			*list_node__option_alloc(t_option const *option_ref, char **argv, size_t i);
void			option_free(t_option **opt);

/*
** path
*/

char 			*path_finder(t_sh *sh, char *commande);

/*
** signal/
*/
void			signal_sigchld(int sig);
int				signal_to_ignore(void);
int				signal_to_default(void);

/*
** lexer/
*/
int			lexer(char const *input, t_lexer *lexer);
t_token		*token_list(void);
int			tokenize(const char *s, t_lexer *lexer);

/*
** termcaps/
*/
int				termcaps_character_to_command_line(const size_t character_bytes_count,
											 const char *character_bytes,
											 t_list_head *command_line);
int				termcaps_display_command_line(const int fd, const t_list_head *command_line);
size_t			termcaps_get_character_bytes_count(const size_t input_bytes_count,
								  const char *input_bytes,
								  size_t *out_missing_bytes_count);
int				termcaps_init(t_sh *sh);
int				termcaps_isunicode(const char c, size_t *out_character_bytes_count);
char			*termcaps_read_input(const t_sh *sh);
int				termcaps_string_to_command_line(const size_t input_buffer_size,
										  const char *input_buffer,
										  t_list_head *command_line);

#endif

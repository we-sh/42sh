#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

# include "shell_typedef.h"
# include "list.h"
# include <unistd.h>
# include "termcaps_struct.h"
# include "option.h"
# include "statuses.h"

/*
** Shell structure
*/

struct					s_sh
{
	pid_t				pgid;
	bool				is_interactive;
	int					fd;
	char				**argv;
	char				**envp;
	t_termcaps_context	termcaps_context;
	int					last_exit_status;
	t_list				opt_head;
	char				*pwd;
	t_list				redir_head;
	int					is_subshell;
};

/*
** Options of the Shell implementation
*/

static t_option			g_sh_option_help = {
	.name = "help",
	.index = ST_OPTION_HELP,
	.is_single_char = 0,
	.has_value = 0,
	.value_is_numeric = 0,
	.value_is_alnum = 0,
	.value_is_indexof = NULL,
	.value = NULL
};

static const t_option	*g_sh_options[] = {
	[0] = &g_sh_option_help,
	[1] = NULL
};

/*
** Others usefull structures
*/

typedef struct dirent	*t_dirent;

#endif

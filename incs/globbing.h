#ifndef GLOBBING_H
# define GLOBBING_H

typedef struct		s_ctx
{
	char			*l;
	char			*m;
	char			*r;
	struct dirent	*c_file;
}					t_ctx;

typedef struct			s_mylist
{
	struct s_mylist		*next;
	char							*content;
}                   t_mylist;

typedef struct s_tmp
{
	int								reverse;
	char							*value;
	char							*before;
	char							*after;
}               t_tmp;

typedef struct s_utils
{
	t_argv		*argument;
	t_argv		*arg;
	t_list		*pos;
	t_list		*safe;
}				t_utils;

int		globbing(t_list **argv_list);
int		globbing_load_context(t_ctx **ctx, char *arg);
void	globbing_context_delete(t_ctx *ctx);
int		globbing_bracket(t_mylist **list, char *input, char *match);
int		globbing_run_parse(t_argv *arg, t_list *list_glob);
int		globbing_run_parse_readir(t_argv *arg, t_list *list_glob, t_ctx *c);
int  	globbing_exp_param_bracket(t_mylist **list,
									char *input,
									t_tmp *concat,
									char *match);
int 	globbing_happend_to_list(t_mylist **list, char *input);
char 	*globbing_check_last_bracket(char *input);
int  	globbing_bracket_exp_subsequence(t_tmp **concat, int i);
void  	globbing_sort_list_glob(t_list **argv_list);
int 	globbing_remove_double(t_tmp **concat);
int  	globbing_bracket_recurse(t_mylist **list, t_tmp *concat, char *match, int i);
int		globbing_before_expand(t_tmp **concat, int i, int len);
int		globbing_check(char *pattern, char *input);
int		globbing_add_node_to_list(t_list *argv_list, t_argv *arg_base);
int		globbing_add_node_alpha_to_list(t_list *list_glob, char *content, t_argv *arg_base);

#endif

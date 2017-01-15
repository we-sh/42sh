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

int		globbing(t_list **argv_list);
int		globbing_load_context(t_ctx **ctx, char *arg);
void	globbing_context_delete(t_ctx *ctx);
int		globbing_bracket(t_mylist **list, char *input, char *match);
int	globbing_run_parse(char *arg, t_list *list_glob);
int		globbing_add_node_to_list(t_list *argv_list, char *content);
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
int       globbing_add_node_alpha_to_list(t_list *argv_list, char *content);
#endif

#ifndef GLOBBING_H
# define GLOBBING_H

typedef struct	s_ctx
{
	char		*l;
	char		*m;
	char		*r;
}				t_ctx;

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
int	globbing_bracket(t_mylist **list, char *input, char *match);
void	globbing_run_parse(char *arg, t_list *list_glob);
int		globbing_add_node_to_list(t_list *argv_list, char *content);
int  globbing_exp_param_bracket(t_mylist **list,
																	char *input,
																	char *after_first_brack,
																	char *endofinput,
																	char *match);
void globbing_happend_to_list(t_mylist **list, char *input);
char *globbing_check_last_bracket(char *input);
int	check_globbing(char *pattern, char *input);
void  globbing_bracket_exp_subsequence(t_tmp **concat, int i);

#endif

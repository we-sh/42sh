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

int		globbing(t_list **argv_list);
int		globbing_load_context(t_ctx **ctx, char *arg);
void	globbing_context_delete(t_ctx *ctx);
void	globbing_bracket(t_mylist **list, char *input);
void	globbing_run_parse(char *arg, t_list *list_glob);
int		globbing_add_node_to_list(t_list *argv_list, char *content);

#endif

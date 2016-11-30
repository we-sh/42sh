#ifndef GLOBBING_H
# define GLOBBING_H

typedef struct	s_ctx
{
	char		*left;
	char		*middle;
	char		*right;
}				t_ctx;

int	globbing_load_context(t_ctx **ctx, char *arg);

#endif

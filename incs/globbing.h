#ifndef GLOBBING_H
# define GLOBBING_H

typedef struct	s_ctx
{
	char		*l;
	char		*m;
	char		*r;
}				t_ctx;

int				globbing_load_context(t_ctx **ctx, char *arg);

void			globbing_context_delete(t_ctx *ctx);

#endif

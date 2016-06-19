#ifndef QUOTING_ENV_H
# define QUOTING_ENV_H

typedef struct			s_quoting
{
	int					quote;
	int					dbquote;
	int					bkquote;
	int					bkslash;
	int					pipe;
}						t_quoting;


int g_child;
int g_in_child;
#endif
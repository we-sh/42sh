#ifndef QUOTING_ENV_H
# define QUOTING_ENV_H


typedef struct			s_quoting
{
	int					quote;
	int					dbquote;
	int					bkquote;
	int					bkslash;
}						t_quoting;

static t_quoting				g_quot_status = {
	.quote = 0,
	.dbquote = 0,
	.bkquote = 0,
	.bkslash = 0
};

#endif
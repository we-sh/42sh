#ifndef HTABL_H
# define HTABL_H
# include "fnv.h"
# define HASH_TABLE_SIZE 5000

/*
** Struct related to path_init_hasht.c
*/

typedef struct			s_hasht
{
	char				*path;
	char				*name;
	struct s_hasht		*next;
}						t_hasht;

typedef struct			s_display_h
{
	int					i;
	int					max;
	int					total_binaries;
	int					folders_nbr;
}						t_display_h;

struct					s_body
{
	t_hasht				*head;
};

struct s_body bodies[HASH_TABLE_SIZE];

#endif

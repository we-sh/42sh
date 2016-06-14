#ifndef HTABL_H
# define HTABL_H
# include "fnv.h"
# define HASH_TABLE_SIZE 5000

/*
*   Struct related to path_init_hasht.c
*/



typedef struct          s_hasht{
    char                *path;
    char                *name;
    struct s_hasht      *next;
}                       t_hasht;

struct body
{
    t_hasht             *head;
};

struct body bodies[HASH_TABLE_SIZE];

#endif /*HTABL_H*/

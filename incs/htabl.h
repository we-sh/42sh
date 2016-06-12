#ifndef HTABL_H
# define HTABL_H

#include "fnv.h"

/*
*   Struct related to path_init_hasht.c
*/

#define HASH_TABLE_SIZE 5000


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

/*
*   Struct related to path_init_hasht.c
*/

#endif /*HTABL_H*/
#ifndef LOCAL_STRUCT_H
# define LOCAL_STRUCT_H

typedef struct			s_var
{
	char				*key;
	char				*value;
	struct s_var		*next;
}						t_var;

#endif

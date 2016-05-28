#ifndef OPTION_H
# define OPTION_H


/*
** Generic structure for options.
** This structure may be used as a list or within a static table.
**
** List use case:
** - parse and save options from `char **argv` at runtime
**
** Static table use case:
** - configure available options for the Shell or a builtin at compilation
**
** Convention:
** - an upcase-single-character option (e.g. `-P`) should be suffixed with `2`
** to differentiate with an optional existing other option with the same
** character in downcase (e.g. `-p`)
*/

typedef struct				s_option
{
	t_list					list_option;
	char const				*name;
	int						description;
	char					is_single_char;
	char					has_value;
	char					value_is_numeric;
	char					value_is_alnum;
	char const				**value_is_indexof;
	char					*value;
}							t_option;

#endif

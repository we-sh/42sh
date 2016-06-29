#ifndef OPTION_H
# define OPTION_H

/*
** Generic structure for options.
** This structure may be used as a list or within a static array.
** List use case:
** - parse and save options from `char **argv` at runtime
** Static table use case:
** - configure available options for the Shell or a builtin at compilation
** Convention:
** - an upcase-single-character option (e.g. `-P`) should be suffixed with `2`
** to differentiate with an optional existing other option with the same
** character in downcase (e.g. `-p`)
** Here is the description of each member of the structure:
** - list_option:      pointers to prev and next
** - name:             name of the option (e.g. `u`, `unset`, `l`)
** - index:            index of builtin
** - is_single_char:   1 or 0, tells if name has to be prefixed with `-` or `--`
** - has_value:        1 or 0, tells if a value should follow in the next field
** - value_is_numeric: 1 or 0, tells if the value must be numeric
** - value_is_alnum:   1 or 0, tells if the value must be alpha-numeric
** - value_is_indexof: NULL or an array of possible values
** - value:            initialized during the parsing or the command line,
**                     it contains a duplication of the next field
** More info on how utility arguments should be implemented:
** http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html
*/

typedef struct				s_option
{
	t_list					list_option;
	char const				*name;
	int						index;
	char					is_single_char;
	char					has_value;
	char					value_is_numeric;
	char					value_is_alnum;
	char const				**value_is_indexof;
	char					*value;
}							t_option;

#endif

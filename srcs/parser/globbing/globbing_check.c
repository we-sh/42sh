#include "shell.h"

/*
** Return 0 if it doesn't match, 1 othewise.
** This function checks if the input string matches with the pattern provided in
** argument.
** It returns 0 if it doesn't match, 1 otherwise.
*/

int			globbing_check(char *pattern, char *input)
{
	char	*is_valid;

	is_valid = 0;
	if (!pattern || !input)
		return (0);
	if (*pattern == -'?')
	{
		return (*input && globbing_check(pattern + 1, input + 1));
	}
	else if (*pattern == -'*')
	{
		return (globbing_check(pattern + 1, input) ||
				(*input && globbing_check(pattern, input + 1)));
	}
	else
	{
		return (*input == *pattern++ && ((*input++ == '\0') ||
					globbing_check(pattern, input)));
	}
}

#include "shell.h"

/*
** This function iterates on tokens while a separator is encountered
** If the argument `char **command` is set, separators are pushed
*/

int	token_parse_utils_skip_separators(t_lexer *lexer, int *i, char **command)
{
	while (*i < lexer->size && TOKEN_TYPE(*i) == TT_SEPARATOR)
	{
		if (command)
			if (token_parse_utils_push_command(TOKEN_CONTENT(*i),
				&j->command) != ST_OK)
				return (ST_MALLOC);
		(*i)++;
	}
	return (ST_OK);
}

#include "shell.h"

/*
** This function takes a string and perform expansions on it in
** the following order (as described here: http://pubs.opengroup.org/onlinep
** ubs/009604499/utilities/xcu_chap02.html#tag_02_06):
** 1. Tilde `~` expansion
*/

char		*expand(t_proc *p, t_lexer_token *token, t_lexer_token *prev_token)
{
	char	*str;

	if ((str = ft_strdup(token->content)) == NULL)
		return (NULL);
	if (!prev_token || prev_token->type != TT_INHIBITOR)
	{
		if ((str = expand_tilde(p, str)) == NULL)
			return (NULL);
	}
	// todo: perform here backslash expansion
	return (str);
}

#include "parser.h"

/*
** These functions are able to apply an action on a specific token received.
** For example, the semi-column token, when it is detected, will return 1,
** which means for the parser that the job is finished.
** WARNING : the parameters should be unconsistent, or some are missing...
** WQRNING : this is one file per token...
*/

int	token_parse_none(t_proc *proc, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s", "TT_NONE");
	log_trace("token type %d token code %d", lexer->tokens[*i].type, lexer->tokens[*i].code);

	char	*tmp;

	// replace with array push in argv
	if (!(proc->command))
		proc->command = ft_strdup(lexer->tokens[*i].content );
	else
	{
		tmp = ft_strjoin(proc->command, lexer->tokens[*i].content);
		free(proc->command);
		proc->command = tmp;
	}
	return (0);
}

#include "parser.h"

/*
** These functions are able to apply an action on a specific token received.
** For example, the semi-column token, when it is detected, will return 1,
** which means for the parser that the job is finished.
** WARNING : the parameters should be unconsistent, or some are missing...
** WQRNING : this is one file per token...
*/

int	token_parse_none(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s", "TT_NONE");
	log_trace("token type %d token code %d", lexer->tokens[*i].type, lexer->tokens[*i].code);

	char	*tmp;
	int		ret;

	if (lexer->tokens[*i].type == TT_NAME && lexer->tokens[*i].code == TC_NONE)
	{
		if ((ret = expand(p, &lexer->tokens[*i], *i > 0 ? &lexer->tokens[*i - 1] : NULL)) != ST_OK)
		{
			log_fatal("failed to push `%s` intro p->argv", lexer->tokens[*i].content);
			return (ret);
		}
	}

	// replace with array push in argv
	if (!(p->command))
		p->command = ft_strdup(lexer->tokens[*i].content );
	else
	{
		tmp = ft_strjoin(p->command, lexer->tokens[*i].content);
		free(p->command);
		p->command = tmp;
	}
	return (0);
}

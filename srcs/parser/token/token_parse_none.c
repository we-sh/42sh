#include "parser.h"

/*
** These functions are able to apply an action on a specific token received.
** For example, the semi-column token, when it is detected, will return 1,
** which means for the parser that the job is finished.
** WARNING : the parameters should be unconsistent, or some are missing...
** WQRNING : this is one file per token...
*/

static int	s_fill_command(t_proc *p, char *content)
{
	char	*tmp;

	if (!(p->command))
		p->command = ft_strdup(content);
	else
	{
		tmp = ft_strjoin(p->command, content);
		free(p->command);
		p->command = tmp;
	}
	if (p->command == NULL)
		return (ST_MALLOC);
	return (ST_OK);
}

int	token_parse_none(t_proc *p, t_lexer *lexer, int *i)
{
	log_trace("entering parsing token %-12s", "TT_NONE");
	log_trace("token type %d token code %d", lexer->tokens[*i].type, lexer->tokens[*i].code);

	char	*content;
	int		ret;
	int		is_inhibited;

	is_inhibited = *i == 0 ? 0 : lexer->tokens[*i - 1].type == TT_INHIBITOR;
	if ((ret = s_fill_command(p, lexer->tokens[*i].content)) != ST_OK)
		return (ret);
	if (!(lexer->tokens[*i].type == TT_NAME
		&& lexer->tokens[*i].code == TC_NONE))
		return (ST_OK);
	if ((ret = token_parse_utils_get_full_word(&content, lexer, i)) != ST_OK)
		return (ret);
	if ((ret = expand(p, content, is_inhibited)) != ST_OK)
	{
		log_fatal("failed to push `%s` intro p->argv", lexer->tokens[*i].content);
		return (ret);
	}
	return (0);
}

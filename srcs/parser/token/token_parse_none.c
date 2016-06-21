#include "parser.h"

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
	if ((ret = expand(lexer->sh, p, content, is_inhibited)) != ST_OK)
	{
		log_fatal("failed to push `%s` intro p->argv", lexer->tokens[*i].content);
		return (ret);
	}
	return (0);
}

#include "shell.h"

int	token_globing_parse_none(void *target, t_parser *parser, t_lexer *lexer, int *i)
{
	log_trace("GLOBBING entering parsing token %-12s", "TT_NONE");

	t_argv	*argument;
	char	*tmp;
	char	*tmp2;
	int		ret;

	(void)parser;
	(void)lexer;
	ret = ST_OK;
	argument = (t_argv *)target;
	if (*i == 0 && TOKEN_CODE(*i) == TC_TILDE)
	{
		tmp = env_get_home(parser->sh->envp);
		if (tmp)
		{
			tmp2 = argument->buffer;
			if ((argument->buffer = ft_strdup(tmp)) == NULL)
				return (ST_MALLOC);
			free(tmp2);
		}
	}
	else
	{
		ret = token_globing_parse_utils_push_str(parser->target_list_head, TOKEN_CONTENT(*i));
	}
	(*i)++;
	return (ST_OK);
}

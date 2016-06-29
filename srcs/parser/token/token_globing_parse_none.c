#include "shell.h"

static int	s_suite(t_parser *parser, t_lexer *lexer, int *i)
{
	int		ret;
	char	*tmp;

	if (TOKEN_CODE(*i) == TC_LASTEXITSTATUS)
	{
		if ((tmp = ft_itoa(parser->sh->last_exit_status)) == NULL)
			return (ST_MALLOC);
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
														tmp);
		free(tmp);
	}
	else
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
														TOKEN_CONTENT(*i));
	return (ret);
}

int			token_globing_parse_none(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	t_argv	*argument;
	char	*tmp;
	char	*tmp2;
	int		ret;

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
		ret = s_suite(parser, lexer, i);
	(*i)++;
	return (ret);
}

#include "shell.h"

static int	s_double_quote(int *i, t_parser *parser, t_lexer *lexer)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = NULL;
	if (TOKEN_CODE(*i) != TC_DQUOTE)
	{
		if ((ret = local_var_replace(parser->sh, TOKEN_CONTENT(*i), &tmp))
			!= ST_OK)
			return (ret);
		ret = token_globing_parse_utils_push_str(parser->target_list_head, tmp);
		free(tmp);
		(*i)++;
	}
	return (ST_OK);
}

int			token_var_parse_inhib(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;

	ret = 0;
	(void)target;
	(*i)++;
	((t_argv *)target)->is_null = 0;
	if (TOKEN_CODE(*i - 1) == TC_QUOTE)
	{
		if (TOKEN_CODE(*i) != TC_QUOTE)
		{
			ret = token_globing_parse_utils_push_str(parser->target_list_head,
															TOKEN_CONTENT(*i));
			(*i)++;
		}
	}
	else if (TOKEN_CODE(*i - 1) == TC_DQUOTE)
	{
		if ((ret = s_double_quote(i, parser, lexer)) != ST_OK)
			return (ret);
	}
	(*i)++;
	return (ret);
}

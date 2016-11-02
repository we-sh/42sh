#include "shell.h"

static char	*s_expand_escape_char_inhibited(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '\\' && str[j + 1] == '\n')
			j += 2;
		else
		{
			if (str[j] == '\\' && str[j + 1] == '\\')
				j++;
			else if (str[j] == '\\' && str[j + 1] == '"' )
				j++;
			str[i] = str[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

int			token_globing_parse_inhib(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;
	
	ret = 0;
	(void)target;
	(*i)++;
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
		if (TOKEN_CODE(*i) != TC_DQUOTE)
		{
			if (TOKEN_CODE(*i) == TC_DOLLAR)
				ret = local_var_replace(parser, i);
			else
				ret = token_globing_parse_utils_push_str(parser->target_list_head,
							s_expand_escape_char_inhibited(TOKEN_CONTENT(*i)));
			(*i)++;
		}
	}
	(*i)++;
	return (ret);
}

#include "shell.h"

#define T_PATTERN_NONE 0
#define T_PATTERN_LIST 1
#define T_PATTERN_RANGE 2

static int	s_get_pattern(t_lexer *lexer, int i)
{
	int		index;
	int		pattern_type;
	int		odd;

	if (i >= lexer->size - 1)
		return (T_PATTERN_NONE);
	index = 0;
	odd = 0;
	pattern_type = T_PATTERN_RANGE;
	while (index + i < lexer->size && TOKEN_CODE(index + i) != TC_RBRACE)
	{
		if (TOKEN_CODE(index + i) == TC_COMMA)
			pattern_type = T_PATTERN_LIST;
		odd = (odd == 1 ? 0 : 1);
		if (pattern_type == T_PATTERN_RANGE)
		{
			if (odd == 1)
			{
			 	if (TOKEN_TYPE(index + i) != TT_NAME)
					pattern_type = T_PATTERN_NONE;
				if (!(ft_strisnumeric(TOKEN_CONTENT(index + i)) == 1
					|| (ft_strlen(TOKEN_CONTENT(index + i)) == 1 && ft_isascii(TOKEN_CONTENT(index + i)[0]))))
					pattern_type = T_PATTERN_NONE;
				if (index == 2 && (ft_strisnumeric(TOKEN_CONTENT(i)) != ft_strisnumeric(TOKEN_CONTENT(index + i))))
					return (T_PATTERN_NONE);
			}
			else if (TOKEN_CODE(index + i) != TC_RANGE)
				pattern_type = T_PATTERN_NONE;
		}
		index++;
	}
	if (pattern_type == T_PATTERN_RANGE && index > 3)
		return (T_PATTERN_NONE);
	if (TOKEN_CODE(index + i) != TC_RBRACE)
		return (T_PATTERN_NONE);
	return (pattern_type);
}

int			token_glob_brace_parse_pattern(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;
	int		pattern_type;
	t_list	*argv_list;

	(void)lexer;
	ret = ST_OK;
	argv_list = (t_list *)target;
	pattern_type = s_get_pattern(lexer, *i + 1);
	if (pattern_type == T_PATTERN_RANGE)
		ret = token_glob_brace_parse_range(parser, argv_list, i);
	(*i)++;
	return (ret);
}

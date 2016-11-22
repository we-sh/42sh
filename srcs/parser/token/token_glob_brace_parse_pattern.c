#include "shell.h"

#define T_PATTERN_NONE 0
#define T_PATTERN_LIST 1
#define T_PATTERN_NUMERIC_RANGE 2
#define T_PATTERN_ASCII_RANGE 3

static int	s_get_pattern_check_token(int pattern_type, t_lexer *lexer,
										int index, int i)
{
	int		is_numeric;

	if (TOKEN_CODE(index + i) == TC_COMMA)
		return (T_PATTERN_LIST);
	if (pattern_type == T_PATTERN_ASCII_RANGE
		|| pattern_type == T_PATTERN_NUMERIC_RANGE)
	{
		if (index % 2 == 0)
		{
			if (TOKEN_TYPE(index + i) != TT_NAME)
				return (T_PATTERN_NONE);
			is_numeric = ft_strisnumeric(TOKEN_CONTENT(index + i));
			if (!(is_numeric == 1 || (ft_strlen(TOKEN_CONTENT(index + i)) == 1
								&& ft_isascii(TOKEN_CONTENT(index + i)[0]))))
				return (T_PATTERN_NONE);
			if (index == 0 && is_numeric == 1)
				return (T_PATTERN_NUMERIC_RANGE);
			if (index == 2 && (ft_strisnumeric(TOKEN_CONTENT(i)) != is_numeric))
				return (T_PATTERN_NONE);
		}
		else if (TOKEN_CODE(index + i) != TC_RANGE)
			return (T_PATTERN_NONE);
	}
	return (pattern_type);
}

static int	s_get_pattern(t_lexer *lexer, int i)
{
	int		index;
	int		pattern_type;

	if (i >= lexer->size - 1)
		return (T_PATTERN_NONE);
	index = 0;
	pattern_type = T_PATTERN_ASCII_RANGE;
	while (index + i < lexer->size && TOKEN_CODE(index + i) != TC_RBRACE)
	{
		pattern_type = s_get_pattern_check_token(pattern_type, lexer, index, i);
		index++;
	}
	if ((pattern_type == T_PATTERN_ASCII_RANGE
		|| pattern_type == T_PATTERN_NUMERIC_RANGE) && index > 3)
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

	if (TOKEN_CODE(*i) != TC_LBRACE)
		return (token_glob_brace_parse_none(target, parser, lexer, i));
	ret = ST_OK;
	argv_list = (t_list *)target;
	pattern_type = s_get_pattern(lexer, *i + 1);
	if (pattern_type == T_PATTERN_NONE)
		ret = token_globing_parse_utils_push_str(parser->target_list_head,
														TOKEN_CONTENT(*i));
	else
	{
		if (pattern_type == T_PATTERN_NUMERIC_RANGE)
			ret = token_glob_brace_parse_numeric_range(parser, argv_list, i);
		else if (pattern_type == T_PATTERN_ASCII_RANGE)
			ret = token_glob_brace_parse_ascii_range(parser, argv_list, i);
		else if (pattern_type == T_PATTERN_LIST)
			ret = token_glob_brace_parse_list(parser, argv_list, i);
	}
	(*i)++;
	return (ret);
}

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
		if (TOKEN_CODE(index + i) == TC_VVIIRRGGUULLEE)
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

static int	s_update_buffer_itoa(t_argv *el, char *original, int value)
{
	char	*tmp;

	if ((tmp = ft_itoa(value)) == NULL)
		return (ST_MALLOC);
	if (el->buffer != NULL)
		free(el->buffer);
	if ((el->buffer = ft_strjoin(original, tmp)) == NULL)
		return (ST_MALLOC);
	free(tmp);
	return (ST_OK);
}

static int	s_process_range(t_parser *parser, int *i)
{
	int		start;
	int		start_original;
	int		end;
	int		dir;

	t_list	*pos;
	t_list	*next;
	t_list	*prev;
	t_argv	*argument;
	char	*original_str;

	start_original = ft_atoi(P_TOKEN_CONTENT(*i + 1));
	end = ft_atoi(P_TOKEN_CONTENT(*i + 3));

	pos = parser->target_list_head;
	while ((pos = pos->next) && pos != parser->target_list_head)
	{
		log_trace("|||||||||||||");
		next = pos->next;
		argument = CONTAINER_OF(pos, t_argv, argv_list);
		if ((original_str = ft_strdup(argument->buffer)) == NULL)
			return (ST_MALLOC);

		prev = pos;
		start = start_original;
		dir = start > end ? -1 : 1;
		while (1)
		{
			if (start != start_original)
			{
				if ((argument = (t_argv *)malloc(sizeof(t_argv))) == NULL)
					return (ST_MALLOC);
				argument->buffer = NULL;
			}
			if (s_update_buffer_itoa(argument, original_str, start) != ST_OK)
				return (ST_MALLOC);

			prev->next = &argument->argv_list;
			if (start != start_original)
			{
				argument->argv_list.prev = prev;
			}
			argument->argv_list.next = next;

			if (start == end)
				break ;
			start += dir;
			prev = &argument->argv_list;
		}

		next->prev = &argument->argv_list;
		pos = &argument->argv_list;
		free(original_str);
	}
	log_trace("------------end");
	*i += 4;
	return (ST_OK);



	return (ST_OK);
}

int			token_glob_brace_parse_pattern(void *target, t_parser *parser,
				t_lexer *lexer, int *i)
{
	int		ret;
	int		pattern_type;

	(void)target;
	ret = ST_OK;
	pattern_type = s_get_pattern(lexer, *i + 1);
	log_trace("--------- `%s`", TOKEN_CONTENT(*i));
	log_trace("pattern_type: %d", pattern_type);
	if (pattern_type == T_PATTERN_RANGE)
		ret = s_process_range(parser, i);
	(void)lexer;
	(void)parser;
	(*i)++;
	return (ret);
}

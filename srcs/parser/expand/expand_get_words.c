#include "shell.h"

static int	s_is_token(char *c, int inhibiter_code)
{
	if (c[0] == '{' || c[0] == '[' || c[0] == '*' || c[0] == '?')
		return (1);
	if (c[0] == '\\' && inhibiter_code == TC_QUOTE)
		return (1);
	return (0);
}

static int	s_get_new_length(char *str, int inhibiter_code)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (s_is_token(str + i, inhibiter_code) == 1)
			len++;
		len++;
		i++;
	}
	return (len);
}

static int	s_is_inhibited(char *start, char *c, int inhibiter_code)
{
	int		odd;

	if (inhibiter_code == TC_QUOTE)
		return (0);
	odd = 0;
	while (c != start)
	{
		c--;
		if (c[0] != '\\')
			return (odd);
		odd = (odd == 0) ? 1 : 0;
	}
	return (odd);
}

static char	*s_build_str(char *content, char *input, int inhibiter_code)
{
	int		k;
	int		j;
	char	*str;
	char	*tmp;

	if ((str = ft_strnew(s_get_new_length(input, inhibiter_code))) == NULL)
		return (NULL);
	j = 0;
	k = 0;
	while (input[j] != '\0')
	{
		if (s_is_token(input + j, inhibiter_code) == 1
			&& s_is_inhibited(input, input + j, inhibiter_code) == 0)
			str[k++] = '\\';
		str[k++] = input[j];
		j++;
	}
	tmp = ft_strjoin(content, str);
	free(str);
	return (tmp);
}

int			expand_get_words(char **content, t_lexer *lexer,
				int *i)
{
	char	*tmp;
	int		is_inhibited = 0;

	if ((*content = ft_strnew(0)) == NULL)
		return (ST_MALLOC);
	while (*i < lexer->size && (TOKEN_TYPE(*i) == TT_INHIBITOR
								|| TOKEN_TYPE(*i) == TT_NAME))
	{
		if (TOKEN_TYPE(*i) == TT_INHIBITOR)
			is_inhibited = (is_inhibited == 0) ? TOKEN_CODE(*i) : 0;
		if (is_inhibited != 0)
			tmp = s_build_str(*content, TOKEN_CONTENT(*i), is_inhibited);
		else
			tmp = ft_strjoin(*content, TOKEN_CONTENT(*i));
		if (tmp == NULL)
			return (ST_MALLOC);
		free(*content);
		*content = tmp;
		(*i)++;
	}
	return (ST_OK);
}

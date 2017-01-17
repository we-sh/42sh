#include "shell.h"

static int	s_is_inhibited(char *start, char *c)
{
	int		odd;

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

static void	s_build_str_2_get_char(char *str, char *input, int *k)
{
	int		l;
	int		has_closing_bracket;

	str[*k] = input[*k];
	l = 1;
	has_closing_bracket = 0;
	while (input[*k + l] != '\0')
	{
		str[*k + l] = input[*k + l];
		if (l > 1 && input[*k + l] == ']'
			&& !(l == 2 && input[*k + l - 1] == '^')
			&& s_is_inhibited(input, input + *k + l) == 0)
		{
			has_closing_bracket = l;
			break ;
		}
		l++;
	}
	if (has_closing_bracket == 0)
		return ;
	str[*k] = -input[*k];
	*k += has_closing_bracket;
}

char		*expand_get_words_special_build_str(char *content, char *input)
{
	int		k;
	char	*str;
	char	*tmp;

	if ((str = ft_strnew(ft_strlen(input))) == NULL)
		return (NULL);
	k = 0;
	while (input[k] != '\0')
	{
		if (input[k] == '[')
			s_build_str_2_get_char(str, input, &k);
		else if (input[k] == '*' || input[k] == '?')
			str[k] = -input[k];
		else
			str[k] = input[k];
		k++;
	}
	tmp = ft_strjoin(content, str);
	free(str);
	return (tmp);
}

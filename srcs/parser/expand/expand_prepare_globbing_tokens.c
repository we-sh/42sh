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

static void	s_build_str_2_get_char(char *content, int *k)
{
	int		l;
	int		has_closing_bracket;

	l = 1;
	has_closing_bracket = 0;
	while (content[*k + l] != '\0')
	{
		if (l > 1 && content[*k + l] == ']'
			&& !(l == 2 && content[*k + l - 1] == '^')
			&& s_is_inhibited(content, content + *k + l) == 0)
		{
			has_closing_bracket = l;
			break ;
		}
		l++;
	}
	if (has_closing_bracket == 0)
		return ;
	content[*k] = -content[*k];
	content[*k + has_closing_bracket] = -content[*k + has_closing_bracket];
	*k += has_closing_bracket;
}

char		*expand_prepare_globbing_tokens(char *content)
{
	int		k;

	k = 0;
	while (content[k] != '\0')
	{
		if (content[k] == '[')
			s_build_str_2_get_char(content, &k);
		else if (content[k] == '*' || content[k] == '?')
			content[k] = -content[k];
		k++;
	}
	return (content);
}

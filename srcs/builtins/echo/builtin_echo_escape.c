#include "shell.h"

static void			s_octal(char *str, size_t *i, size_t *j)
{
	int				tmp;
	int				cnt;
	int				d;
	char			digit[5];
	int				rem;

	d = 0;
	while (ft_isdigit(*(str + *i + 1 + d)) && d < 4)
	{
		digit[d] = *(str + *i + 1 + d);
		d++;
	}
	digit[d] = '\0';
	*i += d;
	tmp = ft_atoi(digit);
	cnt = 0;
	d = 0;
	while (tmp > 0)
	{
		rem = tmp % 10;
		tmp = tmp / 10;
		d += rem * ft_powi(8, cnt);
		cnt++;
	}
	str[*j] = d;
}

static void			s_not_octal(char *str, size_t *i, size_t *j)
{
	if (str[*i + 1] == 'a')
		str[*j] = '\a';
	else if (str[*i + 1] == 'b')
		str[*j] = '\b';
	else if (str[*i + 1] == 'f')
		str[*j] = '\f';
	else if (str[*i + 1] == 'n')
		str[*j] = '\n';
	else if (str[*i + 1] == 'r')
		str[*j] = '\r';
	else if (str[*i + 1] == 't')
		str[*j] = '\t';
	else if (str[*i + 1] == 'v')
		str[*j] = '\v';
	else
		(*i)--;
	(*i)++;
}

char				*builtin_echo_escape(char *str)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '0')
				s_octal(str, &i, &j);
			else
				s_not_octal(str, &i, &j);
		}
		else
		{
			str[j] = str[i];
		}
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
